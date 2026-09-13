#include <stdio.h>
#include <stdlib.h>


//Lista simplesmente encadeada sem nó cabeça ordenada: busca, inserção e remoção ;
//Lista circular simplesmente encadeada sem nó cabeça ordenada: busca, inserção e remoção;
//Lista duplamente encadeada com nó cabeça (sem ordenação): busca, inserção e remoção;
//Fila (FIFO): inserção e remoção;
//Pilha (LIFO): inserção e remoção.



// STRUCTS DE CADA LISTA ---------------------------

// L.SIMPLES
struct LISTA_SIMPLES{
    int chave;
    struct LISTA_SIMPLES *prox;
};

//L.CIRCULAR
struct  LISTA_CIRC{
    int chave;
    struct LISTA_CIRC *prox;
    struct LISTA_CIRC *ini;
    struct LISTA_CIRC *fim;
};

//L.DUPLAMENTE ENCADEADA
struct Lista_Dupla{
    int chave;
    struct Lista_Dupla *prox, *ant;
};

//L.FILA
struct L_FILA{
    int chave;
    struct L_FILA *prox;
};

//L.PILHA
struct L_PILHA{
    int chave;
    struct L_PILHA *prox;
};


//PROCEDIMENTOS PARA A LISTA SIMPLES( ORDENADA )--------------------------

//FUNÇÃO PARA ENCONTRAR UM ELEMENTO NA LISTA
int BUSCA_SIMPLES(struct LISTA_SIMPLES *Lista, int x){
    struct LISTA_SIMPLES *p = Lista;


    if(Lista==NULL){ // LISTA NULO?
        return 0;
    }else{
        p = Lista;
        while(p!=NULL){  //LOOP PARA PERCORRER A LISTA
            if(p->chave==x){ 
                return 1; // SE ENCONTRAR RETORNA VERDADEIRO
            }
            p=p->prox;
        }
    return 0; // RETORNA FALSO SE NÃO ENCONTRAR NO LOOP
    }
}


// PROCEDIMENTO PARA INSERIR ELEMENTOS NA LISTA DE FORMA ORDENADA

void INSERT_SIMPLES(struct LISTA_SIMPLES **Lista, int x){
    struct LISTA_SIMPLES *p = *Lista;
    struct LISTA_SIMPLES *novo = malloc(sizeof(struct LISTA_SIMPLES));
    struct LISTA_SIMPLES *ant=NULL; 

    novo->chave = x;
    novo->prox = NULL;
    
    if(*Lista!=NULL){ // LISTA NULO?
        while(p!=NULL){ // LOOP PARA PERCORRER A LISTA
            if(p->chave > x){ // VERIFICA SE O ELEMENTO DA LISTA É MAIOR
                if(ant == NULL){ // CONDIÇÃO CASO SEJA O MENOR ELEMENTO HA SER INSERIDO
                    novo->prox = p;
                    *Lista = novo;
                    return;
                }else{  // ELSE{  SE O ELEMENTO É DEPOIS DO PRIMEIRO
                    novo->prox = p;
                    ant->prox = novo;
                    return;
                }       
            }else{
                if(p->prox == NULL){ // VERIFICA SE IRA SER O ULTIMO ELEMENTO DA LISTA 
                    p->prox = novo;
                    return;
                }
            }
            ant = p;
            p = p->prox;
        }    
    }else{ // ELSE{ CASO SEJA O PRIMEIRO ELEMENTO HA SER INSERIDO
        novo->prox = *Lista;
        *Lista = novo;
    }
}


// PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA LISTA
void IMPRIMA_SIMPLES(struct LISTA_SIMPLES *Lista){
    struct LISTA_SIMPLES *p = Lista;
    
    if(p!=NULL){ // LISTA VAZIA?
        do{
            printf("[%d]->",p->chave); // IMPRIME AS LISTAS
            p=p->prox;
        }while(p!=NULL); // LOOP PARA PERCORRER A LISTA
    }else{
        printf("NAO EXISTE ELEMENTOS PARA IMPRIMIR\n");
    }
}

// PROCEDIMENTO PARA REMOVER UM ELEMENTO DA LISTA
void REMOVE_SIMPLES(struct LISTA_SIMPLES **Lista, int x){
    struct LISTA_SIMPLES *p = *Lista;  //"P1" PARA PERCORRER A LISTA
    struct LISTA_SIMPLES *ant = NULL; // "ANT" PARA PERCORRER O ANTERIOR DE "P1" 
    
    if(BUSCA_SIMPLES(*Lista,x)==1){ // EXISTE  O ELEMENTO NA LISTA?
        if(p->chave!=x){ // VERIFICA SE O ELEMENTO ESTA NA PRIMEIRA POSIÇÃO DA LISTA
            while(p!=NULL){ // LOOP PARA PERCORRER A LISTA
                if(p->chave==x){ // ACHOU O ELEMENTO ?
                    if(ant!=NULL){
                        ant->prox= p->prox;
                        free(p); // DESALOCA O ELEMENTO REMOVIDO
                    }else{
                        *Lista = p->prox;
                        free(p);
                    }
                    return; // RETORNA CASO JA TENHA REMOVIDO 
                }else{
                    ant=p; 
                    p=p->prox;
                }
            }
        }else{
            (*Lista)= (*Lista)->prox; // SO DAR PROX, CASO SEJA O PRIMEIRO ELEMENTO
            free(p);
        }
    }else{
        printf("\nELEMENTO NAO ENCONTRADO PARA REMOÇÃO\n");
    }
}


// PROCEDIMENTO PARA DESALOCAR TODOS OS ELEMENTOS DA LISTA
void DESALOCA_SIMPLES(struct LISTA_SIMPLES *Lista){

    if(Lista!=NULL){
        if(Lista->prox != NULL){
            DESALOCA_SIMPLES(Lista->prox); // RECURSIVIDADE PARA PERCORRER A LISTA
        }
        free(Lista);
    }

}





// FUNÇOES E PROCEDIMENTOS DA LISTA CIRCULAR-----------------------------------------------------------

// INICIAÇÃO DA LISTA
void Inic_Circu(struct LISTA_CIRC **Lista){
    *Lista = malloc(sizeof(struct LISTA_CIRC));
    (*Lista)->ini = NULL;
    (*Lista)->fim = NULL;
}



// FUNÇÃO PARA ECONTRAR UM ELEMENTO NA LISTA 
int Busca_Circ(struct LISTA_CIRC *lista, int x ){
     struct LISTA_CIRC *aux= lista->ini;

    do{
        if(aux->chave == x){
          return 1; // RETORNE VERDADEIRO CASO TENHA ENCONTRADO
        }
        aux = aux ->prox;
    }while(lista->ini!=aux); //LOOP PARA PERCORRER A LISTA

    return 0; // RETORNA FALSO CASO N TENHA ENCONTRADO
}


//PROCEDIMENTO PARA INSERIR ELEMETOS NA LISTA DE FORMA ORDENADA
void Insert_Circ(struct LISTA_CIRC **lista, int x){
    struct LISTA_CIRC *p = malloc(sizeof(struct LISTA_CIRC));
    struct LISTA_CIRC *aux;
    
    p->chave = x;

    if((*lista)->ini == NULL){  // A LISTA É NULA?
        p->prox = p;
        (*lista)= p;
        (*lista)->ini = p;
        (*lista)->fim = p;
    }else{
        // VERIFICA SE O ELEMENTO ESTA ENTRE O INI E FIM
        if((*lista)->fim->chave>x && (*lista)->ini->chave<x ){
            aux = (*lista)->ini;
            while(aux->prox->chave<x){  
                aux=aux->prox;
            }
            p->prox =aux->prox;
            aux->prox = p;
           
        }else{ // CASO O ELEMENTO HA SER INSERIDO SEJA UM DOS EXTREMOS
            p->prox =  (*lista)->ini;
            (*lista)->fim->prox = p;
        }
        // ATUALIZAÇÃO DO PONTEIRO INI, CASO O ELEMENTO INSERIDO SEJA O MENOR DA LISTA 
        if(p->chave <= (*lista)->ini->chave)
            (*lista)->ini = p;  
            
        // ATUALIZAÇÃO DO PONTEIRO FIM, CASO O ELEMENTO INSERIDO SEJA O MAIOR DA LISTA    
        if(p->chave > (*lista)->fim->chave)
            (*lista)->fim = p;
    }
}


//PROCEDIMETO PARA REMOVER UM ELEMENTO DA LISTA
void Remov_Circ(struct LISTA_CIRC **lista, int x){
    struct LISTA_CIRC *aux;
    struct LISTA_CIRC *ant;// PERCORRER O ANTERIOR DE "AUX"
    int j=0;

    aux  =(*lista)->ini;

    if((*lista)->ini!=NULL){ // LISTA NULA?

        // VERIFICANDO SE EXITE NA LISTA E SE A LISTA NÃO TEM APENAS UM ELEMENTO
        if(Busca_Circ(*lista,x)==1 && (*lista)->ini != (*lista)->fim){
            
            while(aux->chave !=x){ // LOOP PARA PERCORRER A LISTA
                
                //VERIFICAR SE O ELEMENTO DA LISTA HA SER REMOVIDO ESTA APONTADO PELO "FIM"
                if((*lista)->fim->chave ==x){ 
                j=1;
                }
                ant = aux;
                aux = aux->prox;
            }

            if(j==1)
                (*lista)->fim=ant;

        //VERIFICAR SE O ELEMENTO DA LISTA HA SER REMOVIDO ESTA APONTADO PELO "INI"
            if((*lista)->ini->chave!=x){ 
                ant->prox = aux->prox;
            }else{
                (*lista)->ini = (*lista)->ini->prox;
                (*lista)->fim->prox = (*lista)->ini;
            }
            free(aux); // DESALOCA O NO
            
        }else{
            // VERIFICA SE SO EXISTE UM ELEMENTO NA LISTA
             if(Busca_Circ(*lista,x)==1 && (*lista)->ini == (*lista)->fim){
                (*lista)->fim = NULL;
                (*lista)->ini = NULL;
                free(aux);
             }else{
                 printf("\nELEMENTO NAO ENCONTRADO PARA REMOCAO\n");
            }
        }
    }else{
          printf("\nNAO EXISTE ELEMENTOS NA LISTA PARA REMOVER\n");
    }
}


//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS NA LISTA
void Imprima_Circu( struct LISTA_CIRC *lista){
    struct LISTA_CIRC *aux=lista->ini; // RECEBE O INICIO DA LISTA
   

   lista = lista->ini;
   if(aux!=NULL){ // LISTA VAZIA?
        do{
            printf("[%d]-> ",aux->chave);
            aux= aux->prox;
        }while(lista!=aux); // LOOP PARA PERCORRER A LISTA
   }else{
        printf("\nNAO EXISTE ELEMENTOS NA LISTA PARA IMPRIMIR\n");
   }
}


// PROCEDIMENTO PARA DESALOCAR TODOS OS NÓS DA LISTA CIRCULAR
   void DESALOCA_CIRC(struct LISTA_CIRC *lista) {
    if (lista == NULL || lista->ini == NULL) 
        return;

    struct LISTA_CIRC *atual = lista->ini;
    struct LISTA_CIRC *p;

    do {
        p = atual->prox;
        free(atual);
        atual = p;
    } while (atual != lista->ini);

    lista->ini = NULL;
}


// FUNÇOES E PROCEDIMENTOS DA LISTA DUPALMENTE ENCADEADA -------------------------------------------------

// PROCEDIMETO PARA INICIAR A LISTA 
void Inici_Dupla(struct Lista_Dupla **Lista){
 
    *Lista = malloc(sizeof(struct Lista_Dupla));
    (*Lista)->prox = NULL;
    (*Lista)->ant = *Lista; 
}

// FUNÇÃO PARA ENCONTRAR UM ELEMENTO NA LISTA
int Busca_Dupla(struct Lista_Dupla *lista, int x){
    struct Lista_Dupla *p = lista;
    
    while(p!=NULL){ // LOOP PARA PERCORRER A LISTA
        if(p->chave==x){
            return 1; // RETORNA VERDADEIRO, CASO TENHA ENCONTRADO
        }
        p=p->prox;
    }
    return 0; // RETORNA FALSO CASO NÃO TENHA ENCONTRADO

}


// PROCEDIMENTO PARA INSERIR ELEMENTOS NA LISTA
void Insert_Dupla(struct Lista_Dupla **lista, int x) {
    struct Lista_Dupla *p = malloc(sizeof(struct Lista_Dupla));
    struct Lista_Dupla *aux =*lista;

    p->chave =  x;
    p->prox = NULL;

    if(aux->prox==NULL){ // VERIFICA SE JA EXISTE ELEMETO NA LISTA
        p->ant = *lista;
        (*lista)->prox=p;
    }else{
       while(aux->prox!=NULL){ // LOOP PARA PERCORRER A LISTA
            aux = aux->prox;
       }
       p->ant = aux; 
       aux->prox = p;
       
    }
}


// PROCEDIMENTO PARA REMOVER UM ELEMENTO DA LISTA
void Remo_Dupla(struct Lista_Dupla **lista, int x){
    struct Lista_Dupla *p = *lista;
    struct Lista_Dupla *anterior;
    struct Lista_Dupla *pont;

    if(Busca_Dupla(((*lista)->prox),x)==1){ // EXISTE ?
        while(p->chave!= x){ // LOOP PARA PERCORRER A LISTA
            p = p->prox; 
        }
        if(p->prox!=NULL){ // VERIFICA SE É O ULTIMO ELEMENTO
            pont=p->prox;
            anterior = p->ant;

            anterior->prox = pont;
            pont->ant = anterior;  
            free(p);
        }else{
            pont=NULL;
            anterior = p->ant;
            anterior->prox = pont;
            free(p);
        }
    }else{
        printf("\nELEMENTO NAO ENCONTRADO PARA REMOCAO\n");
    }

}



// PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA LISTA
void Imprima_Dupla( struct Lista_Dupla *Lista){
    struct Lista_Dupla *aux = Lista; 

    if(aux->prox!=NULL){ // LISTA VAZIA?
        while(aux!=NULL){// LOOP PARA PERCORRER A LISTA
            printf("[%d]-> ",aux->chave); // IMPRIME A LISTA
            aux= aux->prox;
        }
    }else{
        printf("NAO EXISTE ELEMENTOS NA LISTA PARA IMPRIMIR\n\n");
    }
}


// PROCEDIMETO PARA DESALOCAR TODOS OS NÓS DA LISTA ENCADEADA 
void DESALOCA_DUPLA(struct Lista_Dupla *Lista){

    if(Lista!=NULL){
        if(Lista->prox != NULL){
            DESALOCA_DUPLA(Lista->prox); // RECURSIVIDADE PARA PERCORRER A LISTA
        }
        free(Lista);
    }
}


// PROCEDIMENTOS DA FILA------------------------------------------------

//PROCEDIMENTO PARA INSERIR UM ELEMENTO NA FILA
void INSERT_FILA(struct L_FILA **LISTA_INI, struct L_FILA **LISTA_FIM, int x){
    struct L_FILA *p=malloc(sizeof(struct L_FILA)); 

    p ->chave = x;
    p->prox = NULL;
    
    if((*LISTA_FIM!=NULL)){ // FILA VAZIA?
        (*LISTA_FIM)->prox = p;
    }else{
        *LISTA_INI = p;
    }

    *LISTA_FIM = p;
}


//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS NA FILA
void IMPRIMA_FILA(struct L_FILA *Lista){
  struct L_FILA *p = Lista;
    
    if(p!=NULL){ // PILHA VAZIA?
        do{
            printf("[%d]->",p->chave); // IMPRIMA A FILA
            p=p->prox;
        }while(p!=NULL); // LOOP PARA PERCORRER A FILA
    }else{
        printf("NAO EXISTE ELEMENTOS PARA IMPRIMIR\n");
    }
}



// PROCEDIMENTO PARA IMPRIMIR UM ELEMENTO DA FILA
void REMOVE_FILA(struct L_FILA**INI, struct L_FILA **FIM){
    struct L_FILA*p=*INI;

    if((*INI)!=NULL && (*INI)->prox!=NULL){ // FILA VAZIA? 
        *INI =(*INI)->prox; 

        if((*INI) == NULL){
            (*FIM) = NULL;
            free(p);
        }
    }else{
        if(*INI == *FIM){ // ULTIMO ELEMENTO ?
            (*INI) = NULL;
            (*FIM) = NULL;
             free(p);
        }else{
            printf("FILA VAZIA");
        }
    }
}

// PROCEDIMENTO PAREA DESALOCAR TODOS OS NÓS DA FILA
void DESALOCA_FILA(struct L_FILA *Lista){

    if(Lista!=NULL){
        if(Lista->prox != NULL){
            DESALOCA_FILA(Lista->prox); // RECURSIVIDADE PARA PERCORRER A LISTA
        }
        free(Lista);
    }
}

// PROCEDIMENTOS PARA A PILHA-----------------------------------------------------

//PROCEDIMENTO PARA INSERIR ELEMENTOS NA PILHA
void INSERT_PILHA(struct L_PILHA**Lista, int x){
    struct L_PILHA*p= malloc(sizeof(struct L_PILHA));

    p-> chave =x;
    p->prox = *Lista;
    *Lista = p;

}


//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA PILHA
void IMPRIMA_PILHA(struct L_PILHA *Lista){
  struct L_PILHA *p = Lista;
    
    if(p!=NULL){ // PILHA VAZIA?
        do{
            printf("[%d]->",p->chave); // IMPRIMA A PILHA
            p=p->prox;
        }while(p!=NULL); // LOOP PARA PERCORRER A PILHA
    }else{

        printf("NAO EXISTE ELEMENTOS PARA IMPRIMIR\n");
    }
}


//PROCEDIMENTO PARA REMOVER UM ELEMENTO DA PILHA
void REMOVE_PILHA(struct L_PILHA **Lista){
    struct L_PILHA *p= *Lista;

    if(p!=NULL){// PILHA VAZIA?
    *Lista = (*Lista)->prox;
    free(p);

    }else{
        printf("\nLISTA VAZIA\n");
    }

}




// PROCEDIMENTO PAREA DESALOCAR TODOS OS NÓS DA PILHA
void DESALOCA_PILHA(struct L_PILHA *Lista){

    if(Lista!=NULL){
        if(Lista->prox != NULL){
            DESALOCA_PILHA(Lista->prox); // RECURSIVIDADE PARA PERCORRER A LISTA
        }
        free(Lista);
    }
   
}

//MENUS DE CADA LISTA ------------------------------------------------------------------

// LISTA SIMPLES(ORDENADA)
void MENU_SIMPLES(struct LISTA_SIMPLES **LISTA_Simples){
    struct LISTA_SIMPLES *Lista = *LISTA_Simples;
    int op=0;
    int x;

    while(op!=4){  
        printf("\n----LISTA SIMPLES(ORDENADA)----\n");
        printf("1-IMPRIMIR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");          
        scanf("%d",&op);
       switch(op){
            case 1: // IMPRIMIR 
                IMPRIMA_SIMPLES(Lista); 
            break; 
            case 2: // INSERIR
                printf("\nINSIRA O VALOR:" );    
                scanf("%d",&x);
         	
                INSERT_SIMPLES(&Lista,x);      
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_SIMPLES(Lista); 

            break;   

            case 3: // REMOVER
                printf("\nINSIRA O VALOR:" );   
                scanf("%d",&x);
               
                REMOVE_SIMPLES(&Lista,x);  
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_SIMPLES(Lista); 
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
    *LISTA_Simples = Lista; // ATUALIZAR A LISTA
}





// LISTA CIRCULAR(ORDENADA)
void MENU_CIRCU(struct LISTA_CIRC **Lista_Circ){
    struct LISTA_CIRC *Lista = *Lista_Circ;
    int op=0;
    int x;

    while(op!=4){  
        printf("\n----LISTA CIRCULAR SEM NO CABECA(ORDENADA)----\n");
        printf("1-IMPRIMIR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");          
        scanf("%d",&op);
       switch(op){
            case 1: // IMPRIMIR 
                Imprima_Circu(Lista); 
            break; 

            case 2: // INSERIR
                printf("\nINSIRA O VALOR:" );    
                scanf("%d",&x);
        	
                Insert_Circ(&Lista,x);      
                printf("\nLISTA ATUALIZADA: ");
                Imprima_Circu(Lista); 

            break;   

            case 3: // REMOVER
                printf("\nINSIRA O VALOR:" );   
                scanf("%d",&x);
    
                Remov_Circ(&Lista,x);  
                printf("\nLISTA ATUALIZADA: ");
                Imprima_Circu(Lista); 
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
    *Lista_Circ = Lista; // ATUALIZAR A LISTA
}



// LISTA DUPLAMENTE ENCADEADA
void MENU_DUPLA(struct Lista_Dupla **Lista_Dupla){
    struct Lista_Dupla *Lista = *Lista_Dupla;

    int op=0;
    int x;

    while(op!=4){  
        printf("\n----LISTA DUPLAMENTE ENCADEADA COM NO CABECA----\n");
        printf("1-IMPRIMIR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");          
        scanf("%d",&op);
       switch(op){
            case 1: // IMPRIMIR
                Imprima_Dupla(Lista); 
            break; 

            case 2: // INSERIR
                printf("\nINSIRA O VALOR:" );    
                scanf("%d",&x);
                Insert_Dupla(&Lista,x);     
                printf("\nLISTA ATUALIZADA: ");
                Imprima_Dupla(Lista);   
            break;   

            case 3:// REMOVER
                printf("\nINSIRA O VALOR:" );   
                scanf("%d",&x);
                Remo_Dupla(&Lista,x);  
                printf("LISTA ATUALIZADA: ");
                Imprima_Dupla(Lista); 
            break;

            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
    *Lista_Dupla = Lista; // ATUALIZAR ALISTA
}


//L.FILA
void MENU_FILA(struct L_FILA**LISTA_Fila_INI,struct L_FILA**LISTA_Fila_FIM){
    struct L_FILA *LISTA_INI = *LISTA_Fila_INI;
    struct L_FILA *LISTA_FIM = *LISTA_Fila_FIM;
    int op=0;
    int x;

    while(op!=4){  
        printf("\n----FILA----\n");
        printf("1-IMPRIMIR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");          
        scanf("%d",&op);
       switch(op){
            case 1: // IMPRIMIR 
                IMPRIMA_FILA(LISTA_INI); 
            break; 

            case 2: // INSERIR
                printf("\nINSIRA O VALOR:" );    
                scanf("%d",&x);
                
                INSERT_FILA(&LISTA_INI,&LISTA_FIM,x);      
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_FILA(LISTA_INI); 

            break;   

            case 3: // REMOVER
                
                REMOVE_FILA(&LISTA_INI,&LISTA_FIM);  
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_FILA(LISTA_INI); 
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
    *LISTA_Fila_INI = LISTA_INI; // ATUALIZAR A LISTA
    *LISTA_Fila_FIM = LISTA_FIM;
}




//L.PILHA
void MENU_PILHA(struct L_PILHA **LISTA_Pilha){
    struct L_PILHA *Lista = *LISTA_Pilha;
    int op=0;
    int x;

    while(op!=4){  
        printf("\n----PILHA----\n");
        printf("1-IMPRIMIR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");          
        scanf("%d",&op);
       switch(op){
            case 1: // IMPRIMIR 
                IMPRIMA_PILHA(Lista); 
            break; 

            case 2: // INSERIR
                printf("\nINSIRA O VALOR:" );    
                scanf("%d",&x);
                INSERT_PILHA(&Lista,x);      
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_PILHA(Lista); 

            break;   

            case 3: // REMOVER
                REMOVE_PILHA(&Lista);  
                printf("\nLISTA ATUALIZADA: ");
                IMPRIMA_PILHA(Lista); 
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
    *LISTA_Pilha = Lista; // ATUALIZAR A LISTA
}


int main(){
    int op=1;
    struct Lista_Dupla *Lista_DUPLA;
    struct LISTA_CIRC *Lista_Circ;
    struct LISTA_SIMPLES *Lista_simples =NULL;
    struct L_FILA *L_Fila_INI =NULL;
    struct L_FILA *L_Fila_FIM =NULL;
    struct L_PILHA *L_Pilha = NULL;

    // INICIANDO TODOAS AS LISTAS
    Inici_Dupla(&Lista_DUPLA);
    Inic_Circu(&Lista_Circ);
    
    while(op!=6){
        printf("----LISTA-----\n");
        printf("1-LISTA SIMPLESMENTE ENCADEADA SEM NO CABECA(ORDENADA)\n");
        printf("2-LISTA CIRCULAR SIMPLESMENTE ENCADEADA SEM NO CABECA(ORDENADA)\n");
        printf("3-LISTA DUPLAMENTE ENCADEADA COM NO CABECA\n");
        printf("4-FILA(FIFO)\n");
        printf("5-PILHA(LIFO)\n");
        printf("6-SAIR\n--->");
        scanf("%d",&op);
        
        switch (op){
            case 1: //L.SIMPLES
                MENU_SIMPLES(&Lista_simples);
            break;
            case 2://L.CIRCULAR
                MENU_CIRCU(&Lista_Circ);
                break;
            case 3://L.DUPLAMENTE ENCADEADA
                MENU_DUPLA(&Lista_DUPLA);
            break;
            case 4://FILA
                MENU_FILA(&L_Fila_INI, &L_Fila_FIM);
            break;
            case 5://PILHA
                MENU_PILHA(&L_Pilha);
            break;
            default:
                if(op!=6){
                    printf("OPCAO INVALIDA\n\n");
                }
        }
    }
    DESALOCA_SIMPLES(Lista_simples);
    DESALOCA_CIRC(Lista_Circ);
    DESALOCA_DUPLA(Lista_DUPLA);
    DESALOCA_FILA(L_Fila_INI);
    DESALOCA_PILHA(L_Pilha);
	return 0;
}






