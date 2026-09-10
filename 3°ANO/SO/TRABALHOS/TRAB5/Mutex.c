#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

FILE *saida;

int leitura_concluida = 0;
int filtro_pares_concluido = 0;
int filtro_primos_concluido = 0;

// No da Lista com Mutex
typedef struct LISTA{
    int chave;
    struct LISTA *prox;
    pthread_mutex_t mutex;
}LISTA;

// cabeça da Lista Encadeada
typedef struct{
    LISTA *head;
    LISTA *tail;
    pthread_mutex_t mutex;
}ListaEncadeada;

ListaEncadeada L = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER}; // Inicialização da Lista 

// Função de inserção 
void INSERT(ListaEncadeada *lista, int x){
    LISTA *novo = malloc(sizeof(LISTA));
    if (!novo){
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }

    novo->chave = x;
    novo->prox = NULL;
    pthread_mutex_init(&novo->mutex, NULL);

    pthread_mutex_lock(&lista->mutex);

    if(lista->head == NULL){
        lista->head = novo;
        lista->tail = novo;
    }else{
        // Trava o último elemento para atualizar seu ponteiro prox com segurança
        pthread_mutex_lock(&lista->tail->mutex);
        lista->tail->prox = novo;
        pthread_mutex_unlock(&lista->tail->mutex);
        lista->tail = novo;
    }

    pthread_mutex_unlock(&lista->mutex);
}

// Procedimento para verificar se é primo
int PRIMO(int n){
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Filtro utilizando Hand-Over-Hand Locking (Lock Encadeado)
//Filtro 1 = Pares ,  Filtro 2 = primos
void executar_filtro(int tipo_filtro){
    while (1) {
        pthread_mutex_lock(&L.mutex);
        int fim = leitura_concluida;
        LISTA *anterior = NULL;
        LISTA *atual = L.head;

        if(atual != NULL){
            pthread_mutex_lock(&atual->mutex);
        }
        pthread_mutex_unlock(&L.mutex);

        while(atual != NULL){
            LISTA *proximo = atual->prox;

            // Adquire o lock do próximo nó ANTES de processar (Hand-over-hand locking)
            if(proximo != NULL){
                pthread_mutex_lock(&proximo->mutex);
            }

            int deve_remover = 0;
            if (tipo_filtro == 1) {
                deve_remover = (atual->chave > 2 && (atual->chave % 2 == 0));
            }else{
                deve_remover = (!PRIMO(atual->chave));
            }

            if(deve_remover){
                if(anterior == NULL){
                    // Removendo a cabeça da lista
                    pthread_mutex_lock(&L.mutex);
                    L.head = proximo;
                    if (L.tail == atual){
                        L.tail = NULL;
                    }
                    pthread_mutex_unlock(&L.mutex);
                }else{
                    // Removendo nó do meio ou do fim
                    anterior->prox = proximo;
                    if(L.tail == atual){
                        pthread_mutex_lock(&L.mutex);
                        L.tail = anterior;
                        pthread_mutex_unlock(&L.mutex);
                    }
                }

                // Desbloqueia e destrói o nó removido com segurança
                pthread_mutex_unlock(&atual->mutex);
                pthread_mutex_destroy(&atual->mutex);
                free(atual);

                atual = proximo;
                continue;
            }

            // Se não removeu, solta o lock do nó anterior e avança a janela
            if(anterior != NULL){
                pthread_mutex_unlock(&anterior->mutex);
            }

            anterior = atual;
            atual = proximo;
        }

        if (anterior != NULL){
            pthread_mutex_unlock(&anterior->mutex);
        }

        if(fim){
            pthread_mutex_lock(&L.mutex);
            if (tipo_filtro == 1) filtro_pares_concluido = 1;
            else filtro_primos_concluido = 1;
            pthread_mutex_unlock(&L.mutex);
            break;
        }

        // Evita ocupar 100% da CPU quando a lista está vazia durante a leitura
        usleep(100);
    }
}

// função para entrar no filtro dos pares
void *thread_filtra_pares(void *arg){
    (void)arg;
    executar_filtro(1);
    return NULL;
}

// função para entrar no filtro dos primos
void *thread_filtra_primos(void *arg){
    (void)arg;
    executar_filtro(2);
    return NULL;
}

// Thread de Impressão do arquivo final
void *thread_imprime(void *arg){
    (void)arg;

    // Aguarda a conclusão dos filtros
    while (1){
        pthread_mutex_lock(&L.mutex);
        int pronto = leitura_concluida && filtro_pares_concluido && filtro_primos_concluido;
        pthread_mutex_unlock(&L.mutex);

        if (pronto) break;
        usleep(100);
    }

    pthread_mutex_lock(&L.mutex);
    LISTA *atual = L.head;
    if(atual != NULL){
        pthread_mutex_lock(&atual->mutex);
    }
    pthread_mutex_unlock(&L.mutex);

    while(atual != NULL){
        LISTA *proximo = atual->prox;
        if(proximo != NULL){
            pthread_mutex_lock(&proximo->mutex);
        }

        printf(" %d ", atual->chave);  // imprime no prompt
       
        fprintf(saida, "%d ", atual->chave); // imprimir no arquivo de saida

        pthread_mutex_unlock(&atual->mutex);
        atual = proximo;
    }

    fprintf(saida, "\n");
    fflush(saida);

    return NULL;
}

// Função para desalocar os nó
void liberar_lista(ListaEncadeada *lista){
    LISTA *atual = lista->head;
    while(atual != NULL){
        LISTA *proximo = atual->prox;
        pthread_mutex_destroy(&atual->mutex);
        free(atual);
        atual = proximo;
    }
    pthread_mutex_destroy(&lista->mutex);
}

int main(){
    pthread_t t1, t2, t3;
    FILE *arquivo;
    int x;

    saida = fopen("in.txt.out", "w");  //arquivo de saída
    if(!saida){
        perror("Erro ao criar arquivo de saida");
        return EXIT_FAILURE;
    }

    // Cria as 3 threads adicionais antes/durante a leitura
    pthread_create(&t1, NULL, thread_filtra_pares, NULL);
    pthread_create(&t2, NULL, thread_filtra_primos, NULL);
    pthread_create(&t3, NULL, thread_imprime, NULL);

    arquivo = fopen("in.txt", "r"); // arquivo de leitura
    if(arquivo != NULL){
        while(fscanf(arquivo, "%d", &x) == 1){
            INSERT(&L, x); // adiciona os elemento do arquivo para a Lista
        }
        fclose(arquivo);
    }

    // Sinaliza fim da leitura
    pthread_mutex_lock(&L.mutex);
    leitura_concluida = 1;
    pthread_mutex_unlock(&L.mutex);

    // Aguarda finalização de todas as threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    liberar_lista(&L);
    fclose(saida);

    return EXIT_SUCCESS;
}
