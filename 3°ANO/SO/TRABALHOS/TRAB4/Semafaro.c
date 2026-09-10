#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>


FILE *saida; // ARQUIVO DE SAIDA


// STRUCT PARA LISTA SIMPLES ENCADEADA
struct LISTA {
    int chave;  
    struct LISTA *prox;
};

// STRUCT DE PONTEIROS PARA INICIO E FIM
typedef struct {
    struct LISTA *head;
    struct LISTA *tail;
    pthread_mutex_t mutex;
} ListaEncadeada;

ListaEncadeada L1 = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER}; // INICIALIZADOR 
ListaEncadeada L2 = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER};
ListaEncadeada L3 = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER};

// SEMAFAROS PARA SINCRONIZAÇÃO
sem_t *sem_l1;
sem_t *sem_l2;
sem_t *sem_l3;

//FUNÇÃO PARA INSERIR NO FINAL DA LISTA
void INSERT(ListaEncadeada *lista, int x) {
    struct LISTA *p = (struct LISTA *)malloc(sizeof(struct LISTA));
    if (p == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    p->chave = x;
    p->prox = NULL;

    pthread_mutex_lock(&lista->mutex);
    if (lista->head == NULL) {
        lista->head = p;
        lista->tail = p;
    } else {
        lista->tail->prox = p;
        lista->tail = p;
    }
    pthread_mutex_unlock(&lista->mutex);
}

//FUNÇÃO PARA VERIFICAR SE O ELEMENTO É PRIMO
int PRIMO(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Thread 1: PEGA O L1 , PEGA OS QUE NÃO SÃO PARES E ADCIONA A L2
void *thread_filtra_pares(void *arg) {
    struct LISTA *atual = NULL;

    while (1) {
        sem_wait(sem_l1); // ESPERA O L1

        pthread_mutex_lock(&L1.mutex);
        if (atual == NULL) {
            atual = L1.head;
        } else {
            atual = atual->prox;
        }
        int valor = atual->chave;
        pthread_mutex_unlock(&L1.mutex);

        if (valor == -1) {
            INSERT(&L2, -1);
            sem_post(sem_l2);
            break;
        }

        //FILTRA OS QUE NÃO SÃO PARES MAIORES QUE 2
        if (!(valor % 2 == 0 && valor > 2)) {
            INSERT(&L2, valor);
            sem_post(sem_l2); // NOTIFICA L2
        }
    }
    return NULL;
}

// Thread 2: PEGA L2, PEGA OS PRIMOS E ADCIONA EM L3
void *thread_filtra_primos(void *arg) {
    struct LISTA *atual = NULL;

    while (1) {
        sem_wait(sem_l2); //AGUARDA L2

        pthread_mutex_lock(&L2.mutex);
        if (atual == NULL) {
            atual = L2.head;
        } else {
            atual = atual->prox;
        }
        int valor = atual->chave;
        pthread_mutex_unlock(&L2.mutex);

        if (valor == -1) {
            INSERT(&L3, -1);
            sem_post(sem_l3);
            break;
        }

        // MANTEM APENAS NUMEROS PRIMOS
        if (PRIMO(valor)) {
            INSERT(&L3, valor);
            sem_post(sem_l3); // NOTIFICA L3
        }
    }
    return NULL;
}

// Thread 3: PEGA L3 E GUARDA OS VALORES NO ARQUIVO DE SAIDA
void *thread_imprime(void *arg) {
    struct LISTA *atual = NULL;

    while (1) {
        sem_wait(sem_l3); // AGUARDA L3

        pthread_mutex_lock(&L3.mutex);
        if (atual == NULL) {
            atual = L3.head;
        } else {
            atual = atual->prox;
        }
        int valor = atual->chave;
        pthread_mutex_unlock(&L3.mutex);

        if (valor == -1) break; 

        fprintf(saida,"%d ",valor); // GUARDA OS VALORES NO ARQUIVO DE SAIDA

        fflush(stdout);
    }
    return NULL;
}


// FUNÇÃO PARA LIBERAR LISTA
void liberar_lista(ListaEncadeada *lista) {
    struct LISTA *atual = lista->head;
    struct LISTA *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    lista->head = NULL;
    lista->tail = NULL;
}



int main(int argc, char *argv[]) {
    pthread_t t1, t2, t3;
    char nomeSaida[100]; // VETOR PARA GUARDAR O NOME DO ARQUIVO
    
    // CASO A QUANTIDADE DE ARGUMENTOS SEJA SUFICIENTE
    if(argc < 2){ 
        printf("Uso: %s ARGUMENTOS INSUFICIENTE\n", argv[0]);
        return 1;
    }



    
    sprintf(nomeSaida,"%s.out",argv[1]);
    saida = fopen(nomeSaida,"w");

    if(saida==NULL){
        printf("Erro ao criar arquivo.\n");
        return 1;
    }

    // LIMPA SEMAFAROS ANTIGOS
    sem_unlink("/sem_l1");
    sem_unlink("/sem_l2");
    sem_unlink("/sem_l3");

    // INICIAR OS SEMAFAROS
    sem_l1 = sem_open("/sem_l1", O_CREAT, 0644, 0);
    sem_l2 = sem_open("/sem_l2", O_CREAT, 0644, 0);
    sem_l3 = sem_open("/sem_l3", O_CREAT, 0644, 0);

    if (sem_l1 == SEM_FAILED || sem_l2 == SEM_FAILED || sem_l3 == SEM_FAILED) {
        perror("Erro ao abrir semáforos nomeados");
        exit(1);
    }

    //  CRIANDO 3 THREADS 
    pthread_create(&t1, NULL, thread_filtra_pares, NULL);
    pthread_create(&t2, NULL, thread_filtra_primos, NULL);
    pthread_create(&t3, NULL, thread_imprime, NULL);

    // LE O ARQUIVO ENVIADO 
    FILE *arquivo = fopen(argv[1], "r"); // ABRE O ARQUIVO DE ENTRADA 
    if (arquivo == NULL) {
        perror("Erro ao abrir ");
        exit(1);
    }

    int x;
    while (fscanf(arquivo, "%d", &x) == 1) {
        INSERT(&L1, x);
        sem_post(sem_l1); // NOTIFICA L1 QUE O ELEMENTO ENTROU
    }
    fclose(arquivo); // FECHA O ARQUIVO DE ENTRADA
    

    // ENVIA O SINALIZADOR
    INSERT(&L1, -1);
    sem_post(sem_l1);

    // AGUARDA O ENCERRAMENTOS DE TODAS AS THREADS
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // FECHAMENTO DOS SEMAFAROS
    sem_close(sem_l1);
    sem_close(sem_l2);
    sem_close(sem_l3);
    sem_unlink("/sem_l1");
    sem_unlink("/sem_l2");
    sem_unlink("/sem_l3");

    //LIBERAÇÃO DE MEMORIA
    liberar_lista(&L1);
    liberar_lista(&L2);
    liberar_lista(&L3);

    fclose(saida); // FECHA O ARQUIVO DE SAIDA
    return 0;
}
