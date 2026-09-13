#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include <unistd.h>
//Busca, inserção e remoção em lista simplesmente encadeada sem nó cabeça ordenada;
//Busca, inserção e remoção em lista circular simplesmente encadeada sem nó cabeça ordenada;
//Busca, inserção e remoção em lista duplamente encadeada com nó cabeça (sem ordenação);
//Inserção e remoção em fila (FIFO);
//Inserção e remoção em pilha (LIFO).





// STRUCT DA LISTA SIMPLESMENTE ENCADEADA SEM NÓ CABEÇA, PILHA E FILA
 typedef struct SIMPLES{ 
	int chave;
	struct SIMPLES *prox;
}simples;

// STRUCT DA LISTA DUPLAMENTE ENCADEADA
 typedef struct DUPLA{ 
	int chave;
	struct dupla *prox;
    struct dupla *ant;
}dupla;


//STRUCT PARA A LISTA CIRCULAR EMCADEADA ORDENADA
typedef struct circular{
    int chave;
    struct circular *prox;
}cir;

typedef struct{
    cir *inicio;
    cir *fim;
    int tam;
}LISTA_C;

//PROCEDIMENTO PARA INICIALIZAR A LISTA SIMPLESMENTE ENCADEADA , A PILHA E A FILA
void inicia_LPF(simples **lista, simples **pilha, simples **fila){
    *lista=NULL;
    *pilha=NULL;
    *fila=NULL;
}

//PROCEDIMENTO PARA INICIALIZAR A LISTA DUPLAMENTE ENCADEADA
void inicia_dupla(dupla **lista){

    (*lista)->prox=NULL;
    (*lista)->ant=*lista;
}

//PROCEDIMENTO PARA INICIALIZAR A LISTA CIRCULAR
void inicia_cir(LISTA_C **lista){
    (*lista)->inicio = NULL;
    (*lista)->fim = NULL;
    (*lista)->tam = 0;
}

//PROCEDIMENTO PARA INSERIR VALORES ORDENAMENTE NA LISTA SIMPLESMENTE ENCADEADA
void insere(simples **lista, int num){
    simples *aux, *novo = malloc(sizeof(simples));

    novo->chave = num;  
    if(*lista == NULL){   // condição se a lista estiver vazia 
        novo->prox = NULL;
        *lista = novo;
    }else{
        if(novo->chave < (*lista)->chave){ // VERIFICAR SE O PRIMEIRO ELEMENTO DA LISTA É MAIOR QUE O NOVO VALOR
            novo->prox = *lista;
            *lista = novo;
        }else{                           // SE NÃO FOR, PERCORRE A LISTA ATE ACHAR O VALOR QUE É MAIOR QUE O NOVO VALOR
            aux = *lista;
            while(aux->prox && novo->chave > aux->prox->chave){     // LOOP PARA ACHAR O VALOR MAIOR QUE O NOVO VALOR
                aux = aux->prox;    
            }   
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}

//FUNÇÃO DE BUSCA PARA VERIFICAR SE EXISTE O ELEMENTO X NA LISTA SIMPLESMENTE ENCADEADA ORDENADA 
// RETORNE 0(SE NÃO EXISTIR) OU 1( SE EXISTIR)
int busca(simples  **lista, int val){
	simples *p = malloc(sizeof(simples));
    int verifica =0;

    p=*lista;

    while(p!=NULL){
        if(p->chave == val){  // CONDIÇÃO SE O ELEMENTO DA LISTA FOR IGUAL AO VALOR PROCURADO
            verifica =1;
        }
        p= p->prox;
    }
    return verifica;     // RETORNE 0 OU 1

}

//RPOCEDIMENTO PARA REMOVER UM ELEMENTO NA LISTA SIMPLESMENTE ENCADEADA ORDENADA 
simples* remover(simples **lista, int num){
    simples *aux, *remove = NULL;

    if((*lista)->chave == num){  // CONDIÇÃO PARA VERIFICAR SE O PRIMEIRO ELEMENTO É IGUAL AO ELEMENTO HA SER REMOVIDO
         remove = *lista;
        *lista = remove->prox;
    }else{                       // SE NÃO FOR , PERCORRE A LISTA ATE ACHAR O ELEMENTO HA SER REMOVIDO
        aux = *lista;
        while(aux->prox && aux->prox->chave != num)  // LOOP PARA ACHAR O ELEMENTO HA SER REMOVIDO
            aux = aux->prox;
        if(aux->prox){
            remove = aux->prox;
            aux->prox = remove->prox;
        }
    }
}

//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA LISTA SIMPLEMENTE ENCADEADA ORDENADA
void imprima(simples **lista){
    simples *p = malloc(sizeof(simples));
    char text[250];
    int x=50, y=100, w=65;
    p=*lista;
    gfx_init(800, 200, "Teste!");
    while( p != NULL )      // LOOP PARA PERCORRER A LISTA
	{
	        sprintf(text,"%i",p->chave);
	        
	        gfx_set_color(255, 0, 0);
	        gfx_rectangle(x, 50, y, 100);
          	
          	gfx_set_color(0, 255, 0);
	        gfx_text(w, 65, text);
		p = p->prox;
		x=x+100;
		y=y+100;
		w=w+100;
	}	
	gfx_paint();

	sleep(5);

	gfx_quit();
}

//PROCEDIMENTO PARA INSERIR ELEMENTO NA LISTA CIRCULAR CASO A LISTA SEJA NULO OU CASO O 
// PRIMEIRO ELEMENTO SEJA MAIOR QUE O ELEMENTO A SER INSERDO
void ini(LISTA_C **lista, int num){
    cir *novo = malloc(sizeof(cir));

        novo->chave = num;
        novo->prox = (*lista)->inicio;
        (*lista)->inicio = novo;
        if((*lista)->fim == NULL) //CONDIÇÃO PARA VERIFICAR SE O FIM DA LISTA É NULL
            (*lista)->fim = novo;
        (*lista)->fim->prox = (*lista)->inicio;
        (*lista)->tam++;

}

//PROCEDIMENTO PARA INSERIR ELEMENTOS NA LISTA CIRCULAR
void insere_cic(LISTA_C **lista, int num){

    cir *aux, *novo = malloc(sizeof(cir));

        novo->chave = num;
        if((*lista)->inicio == NULL){  // CONDIÇÃO PARA VERIFICAR SE A LISTA É NULO
              novo->chave = num;
        novo->prox = (*lista)->inicio;
        (*lista)->inicio = novo;
        if((*lista)->fim == NULL) //CONDIÇÃO PARA VERIFICAR SE O FIM DA LISTA É NULL
            (*lista)->fim = novo;
        (*lista)->fim->prox = (*lista)->inicio;
        (*lista)->tam++;

        }
        else if(novo->chave < (*lista)->inicio->chave){ //CONDIÇÃO PARA VERIFICAR SE O PRIMEIRO ELEMENTO DA LISTA É MAIOR QUE O ELEMENTA HA SER INSERIDO
                novo->chave = num;
        novo->prox = (*lista)->inicio;
        (*lista)->inicio = novo;
        if((*lista)->fim == NULL) //CONDIÇÃO PARA VERIFICAR SE O FIM DA LISTA É NULL
            (*lista)->fim = novo;
        (*lista)->fim->prox = (*lista)->inicio;
        (*lista)->tam++;

        }
        else{
            aux = (*lista)->inicio;
            while(aux->prox != (*lista)->inicio && novo->chave > aux->prox->chave) //LOOP PARA ACHAR O VALOR MAIOR QUE O NOVO VALOR
                aux = aux->prox;
            if(aux->prox == (*lista)->inicio){

                if((*lista)->inicio == NULL){
                (*lista)->inicio = novo;
                (*lista)->fim = novo;
                (*lista)->fim->prox = (*lista)->inicio;
            }
            else{
                (*lista)->fim->prox = novo;
                (*lista)->fim = novo;
                (*lista)->fim->prox = (*lista)->inicio;
            }
             (*lista)->tam++;
        
            }else{

                novo->prox = aux->prox;
                aux->prox = novo;
                (*lista)->tam++;
            }
        }
}


//FUNÇÃO DE BUSCA PARA A LISTA CIRCULAR ORDENADA
// RETORNE 0(SE NÃO EXISTIR) OU 1( SE EXISTIR)
int busca_cir(LISTA_C **lista, int x){
    int retorne=0;

    for(int i=0;i<(*lista)->tam;i++){      //LOOP PARA PERCORRER TODA A LISTA
        if((*lista)->inicio->chave == x)   // CONDIÇÃO PARA VERIFICAR SE O VALOR É ENCONTRADO
            retorne = 1;
        
        (*lista)->inicio = (*lista)->inicio->prox;
    }
    (*lista)->inicio=(*lista)->fim->prox;
    return retorne;
}

//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA LISTA CIRCULAR ORDENADA
void imprime_cir(LISTA_C **lista){
     gfx_init(800, 200, "Teste!");
     char text[250];
     int x=50, y=100, w=65;
    for(int i=0;i<(*lista)->tam;i++){  //LOOP PARA PERCORRER TODA A LISTA
      
	        sprintf(text,"%i",(*lista)->inicio->chave);
	        
	        gfx_set_color(255, 0, 0);
	        gfx_rectangle(x, 50, y, 100);
          	
          	gfx_set_color(0, 255, 0);
	        gfx_text(w, 65, text);
		x=x+100;
		y=y+100;
		w=w+100;
  
        (*lista)->inicio=(*lista)->inicio->prox;
    }
    (*lista)->inicio=(*lista)->fim->prox;
    gfx_paint();

	sleep(5);

	gfx_quit();
}



//FUNÇÃO PARA REMOVER UM ELEMENTO DA LISTA CIRCULAR ORDENADA
// RETORNE A LISTA COM O VALOR REMOVIDO 
cir* remove_cir(LISTA_C **lista, int num){
    cir *aux, *remover = NULL;

    if((*lista)->inicio){ // CONDIÇÃO PARA VERIFICAR SE A LISTA É NULA
        if((*lista)->inicio == (*lista)->fim && (*lista)->inicio->chave == num){ // CONDIÇÃO PARA VERIFICAR SE A LISTA TEM 1 ELEMENTO E SE O ELEEMNTO É IGUAL AO VALOR PROCURADO
            remover = (*lista)->inicio;
            (*lista)->inicio = NULL;
            (*lista)->fim = NULL;
            (*lista)->tam--;
        }
        else if((*lista)->inicio->chave == num){ //CONDIÇÃO PARA VERIFICAR SE A LISTA TIVER MAIS DE 1 ELEMENTO E SE O PRIMEIRO ELEMEMTO É IGUAL AO VALOR PROCURADO
            remover = (*lista)->inicio;
            (*lista)->inicio = remover->prox;
            (*lista)->fim->prox = (*lista)->inicio;
            (*lista)->tam--;
        }
        else{          // CASO CONTRARIO , PERCORRE TODA A LISTA ATÉ ACHAR O VALOR PROCURADO 
            aux = (*lista)->inicio;
            while(aux->prox != (*lista)->inicio && aux->prox->chave != num) // LOOP PARA PERCORRER A LISTA ATE O VALOR PROCURADO
                aux = aux->prox;
            if(aux->prox->chave == num){   // CONDIÇÃO PARA VERIFICAR SE O ELEMENTO É IGUAL AO VALOR PROCURADO
                if((*lista)->fim == aux->prox){
                    remover = aux->prox;
                    aux->prox = remover->prox;
                    (*lista)->fim = aux;
                }
                else{
                    remover = aux->prox;
                    aux->prox = remover->prox;
                }
                (*lista)->tam--;
            }
        }
    }
    return remover;
}

//PROCEDIMENTO PARA INSERIR ELEMENTO NA LISTA DUPLAMENTE ENCADEADA
void insere_dupla(dupla **lista, int val){
    dupla *p=malloc(sizeof(dupla));

    p->chave =  val;
    p->prox = *lista;
    p->ant = NULL;
    if(*lista!=NULL){ // CONDIÇÃO PARA VERIFICAR SE HA ELEMENTO NA LISTA
        (*lista)->ant = p;
    }
    *lista = p;
}

//PROCEDIMENTO PARA IMPRIMIR OS ELEMENTOS DA LISTA DUPLAMENTE ENCADEADA 
void imprima_dupla(dupla **lista){
    dupla *p = malloc(sizeof(dupla));
    char text[250];
    int x=50, y=100, w=65;
    p=*lista;
    gfx_init(800, 200, "Teste!");
    while( p != NULL )      // LOOP PARA PERCORRER A LISTA
	{
	        sprintf(text,"%d",p->chave);
	        
	        gfx_set_color(255, 0, 0);
	        gfx_rectangle(x, 50, y, 100);
          	
          	gfx_set_color(0, 255, 0);
	        gfx_text(w, 65, text);
		p = p->prox;
		x=x+100;
		y=y+100;
		w=w+100;
	}	
	gfx_paint();

	sleep(5);

	gfx_quit();	
}

//FUNÇÃO DE BUSCA PARA VERIFICAR SE EXISTE O ELEMENTO X NA LISTA DUPLAMENTE ENCADEADA
// RETORNE 0(SE NÃO EXISTIR) OU 1( SE EXISTIR)
int busca_dupla(dupla  **lista, int val){
	dupla *p = malloc(sizeof(dupla));
    int verifica =0;

    p=*lista;
    
    while(p!=NULL){ // LOOP PARA PERCORRER TODA A LISTA
        if(p->chave == val){  // CONDIÇÃO SE O ELEMENTO DA LISTA FOR IGUAL AO VALOR PROCURADO
            verifica =1;
        }
        p= p->prox;
    }
    return verifica;     // RETORNE 0 OU 1

}


//PROCEDIMENTO PARA INSERIR ELEMENTOS NA PILHA E FILA
void insere_PF(simples **lista, int x){
    simples *p2, *p = malloc(sizeof(simples));

    p->chave = x;
    p->prox = NULL;

    if(*lista == NULL){  // CONDIÇÃO PARA VERIFICAR SE HA ELEMENTO NA LISTA;
        *lista = p;
    }else{
        p2=*lista;
        while(p2->prox){
            p2=p2->prox;        
        }
        p2->prox = p;
    }
}

//PROCEDIMENTO PARA REMOVER UM ELEMENTO DA PILHA 
void remove_Pilha(simples **lista ){
    simples *p2=malloc(sizeof(simples));

    if((*lista)->prox == NULL){ // CONDIÇÃO PARA VERIFICAR SE A LISTA TEM 1 ELEMENTO 
        *lista = NULL;
    }else{
        p2 =*lista;
        while(p2->prox->prox!=NULL)
            p2=p2->prox;
        p2->prox=NULL;
    }
}


//MENU DO LISTA SIMPLEMENTE ENCADEADA ORDENADA 
void MENUSIMPLES(){
	int op, x, b;
    simples *L=NULL;

    while(op!=4){   // LOOP PARA MOSTRAR ATE O USUARIO QUISER SAIR DO MENU
        printf("\n----LISTA SIMPLESMENTE ENCADEADA SEM NO CABECA(ORDENADA)----\n");
        printf("0-IMPRIMIR\n1-BUSCAR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");               // OPÇÕES DO MENU HA SER ESCOLHIDOS 
        scanf("%d",&op);
       switch(op){
            case 0:
                if(L!=NULL)
                    imprima(&L);    // OPÇÃO DE IMPRIMIR A LISTA
                else
                printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break; 
            case 1:
                printf("\nINSIRA O VALOR DE BUSCA: "); 
                scanf("%d",&x);             
                b=busca(&L,x);// BUSCA UM ELEMENTO DA LISTA 

                if(b==1){   // CONDIÇÃO PARA VERIFICAR SE HA O ELEMENTO MA LISTA
                    printf("\nESSE ELEMENTO EXISTE NA LISTA\n\n");
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
        
            case 2:
                printf("\nINSIRA O VALOR:" );    // OPÇÃO PARA INSERIR UM ELEMENTO NA LISTA
                scanf("%d",&x);
                printf("\nVALOR %d INSERIDO NA LISTA\n\n",x);	
                insere(&L,x);       // FUNÇÃO PARA INSERIR O ELEMENTO 
            break;   
            
            case 3:
                printf("\nINSIRA O VALOR:" );   // OPÇÃO PARA REMOVER UM ELEMENTO
                scanf("%d",&x);
                b=busca(&L,x);      //FUNÇÃO PARA VERIFICAR SE EXISTE O ELEEMNTO NA LISTA
                if(b==1){           // CONDIÇÃO PARA VERIFICAR SE O ELEMENTO EXISTE NA LISTA PARA SER REMOVIDO
                    printf("\nVALOR %d REMOVIDO\n\n",x);
                    remover(&L,x);  // SE CONDIÇÃO FOR VERDADEIRA , REMOVE O PRIMEIRO ELEMEMTO ENCONTRADO 
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
}


//MENU DO LISTA CIRCULAR ORDENADA
void MENUCIR(){
    LISTA_C *L=malloc(sizeof(LISTA_C));
    inicia_cir(&L);

     inicia_cir(&L);
	int op, x, b;
    while(op!=4){   // LOOP PARA MOSTRAR ATE O USUARIO QUISER SAIR DO MENU
        printf("\n----LISTA CIRCULAR CIRCULAR ENCADEADA SEM NO CABECA(ORDENADA)----\n");
        printf("0-IMPRIMIR\n1-BUSCAR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");               // OPÇÕES DO MENU HA SER ESCOLHIDOS 
        scanf("%d",&op);
       
       switch(op){
            case 0:
                if(L->inicio!=NULL)
                    imprime_cir(&L);  // OPÇÃO DE IMPRIMIR A LISTA
                else
                printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break; 
        
            case 1:
                printf("\nINSIRA O VALOR DE BUSCA: "); 
                scanf("%d",&x);             
                b=busca_cir(&L,x);// BUSCA UM ELEMENTO DA LISTA 

                if(b==1){   // CONDIÇÃO PARA VERIFICAR SE HA O ELEMENTO MA LISTA
                    printf("\nESSE ELEMENTO EXISTE NA LISTA\n\n");
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
            case 2:
                printf("\nINSIRA O VALOR:" );    // OPÇÃO PARA INSERIR UM ELEMENTO NA LISTA
                scanf("%d",&x);
                printf("\nVALOR %d INSERIDO NA LISTA\n\n",x);	
                insere_cic(&L,x);       // FUNÇÃO PARA INSERIR O ELEMENTO 
            break;   
            case 3:
                printf("\nINSIRA O VALOR:" );   // OPÇÃO PARA REMOVER UM ELEMENTO
                scanf("%d",&x);
                b=busca_cir(&L,x);      //FUNÇÃO PARA VERIFICAR SE EXISTE O ELEEMNTO NA LISTA
                if(b==1){           // CONDIÇÃO PARA VERIFICAR SE O ELEMENTO EXISTE NA LISTA PARA SER REMOVIDO
                    printf("\nVALOR %d REMOVIDO\n\n",x);
                    remove_cir(&L,x);  // SE CONDIÇÃO FOR VERDADEIRA , REMOVE O PRIMEIRO ELEMEMTO ENCONTRADO 
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
}


//MENU DO LISTA DUPLAMENTE ENCADEADA 
void MENUSDUPLA(){
    dupla *L;
    inicia_dupla(L);
	int op, x, b;
    while(op!=4){   // LOOP PARA MOSTRAR ATE O USUARIO QUISER SAIR DO MENU
        printf("\n----LISTA DUPLAMENTE ENCADEADA COM NO CABECA----\n");
        printf("0-IMPRIMIR\n1-BUSCAR\n2-INSERIR\n3-REMOVER\n4-SAIR\n--->");               // OPÇÕES DO MENU HA SER ESCOLHIDOS 
        scanf("%d",&op);
       
       switch(op){
            case 0 :
                if(L->prox!=NULL)
                    imprima_dupla(&L);    // OPÇÃO DE IMPRIMIR A LISTA
                else
                    printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break;
            case 1:
                printf("\nINSIRA O VALOR DE BUSCA: "); 
                scanf("%d",&x);             
                b=busca_dupla(&L,x);// BUSCA UM ELEMENTO DA LISTA 

                if(b==1){   // CONDIÇÃO PARA VERIFICAR SE HA O ELEMENTO MA LISTA
                    printf("\nESSE ELEMENTO EXISTE NA LISTA\n\n");
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
        
            case 2:
                printf("\nINSIRA O VALOR:" );    // OPÇÃO PARA INSERIR UM ELEMENTO NA LISTA
                scanf("%d",&x);
                printf("\nVALOR %d INSERIDO NA LISTA\n\n",x);	
                insere_dupla(&L,x);       // FUNÇÃO PARA INSERIR O ELEMENTO 
            break;    
            
            case 3:
                printf("\nINSIRA O VALOR:" );   // OPÇÃO PARA REMOVER UM ELEMENTO
                scanf("%d",&x);
                b=busca(&L,x);      //FUNÇÃO PARA VERIFICAR SE EXISTE O ELEEMNTO NA LISTA
                if(b==1){           // CONDIÇÃO PARA VERIFICAR SE O ELEMENTO EXISTE NA LISTA PARA SER REMOVIDO
                    printf("\nVALOR %d REMOVIDO\n\n",x);
                    remover(&L,x);  // SE CONDIÇÃO FOR VERDADEIRA , REMOVE O PRIMEIRO ELEMEMTO ENCONTRADO 
                }else{
                    printf("\nESSE ELEMENTO NAO EXISTE NA LISTA\n\n");
                }
            break;
            default:
                if(op!=4){
                    printf("OPCAO INVALIDA");
                }
       }
    }
}



// MENU DA FILA
void MENUFILA(){
      int op, x;
      simples *PF=NULL;
      do{  // LOOP PARA PERCORRER O MENU ATE O USUARIO QUISER SAIR
        printf("\n---- FILA ----\n");
        printf("0-IMPRIMIR\n1-INSERIR\n2-REMOVER\n3-SAIR\n--->");
        scanf("%d",&op);

        switch(op){
            case 0:
                if(PF!=NULL)
                    imprima(&PF);  // PROCEDIMENTO PRARA IMPRIMIR 
                else
                    printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break;
            case 1:
                printf("\nINSIRA O VALOR: ");
                scanf("%d",&x);
                printf("\nVALOR %d INSERIDO NA FILA\n",x);
                insere_PF(&PF,x);
            break;
            case 2:
            if(PF!=NULL){
                remover(&PF,PF->chave);
                 printf("\nITEM REMOVIDO DA FILA\n\n");
            }else
                printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break;
            default:
            if(op!=3){
                printf("OPCAO INVALIDA\n\n");
            }
        }
    }while(op!=3);
}

//MENU DA PILHA
void MENUPILHA(){
    simples *PF = NULL;

    int op, x;
    do{
        printf("\n---- PILHA ----\n");
        printf("0-IMPRIMIR\n1-INSERIR\n2-REMOVER\n3-SAIR\n--->");
        scanf("%d",&op);

        switch(op){

            case 0:
               if(PF!=NULL)
                    imprima(&PF);  // PROCEDIMENTO PRARA IMPRIMIR 
                else
                    printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break;
            case 1:
                printf("\nINSIRA O VALOR: ");
                scanf("%d",&x);
                printf("\nVALOR %d INSERIDO NA PILHA\n",x);
                insere_PF(&PF,x);
            break;
            case 2:
            if(PF !=NULL){
                remove_Pilha(&PF);
                printf("\nITEM REMOVIDO DA PILHA\n\n");
            }else
                printf("\n\nNAO HA ELEMENTO NA LISTA\n\n");
            break;
            default:
            if(op!=3){
                printf("OPCAO INVALIDA\n\n");
            }
        }
    }while(op!=3);
}


//FUNÇÃO PARA ESCOLHER O TIPO DE LISTA 
int main()
{
    int op=1;
   
    while(op!=6){
        printf("----LISTA-----\n");
        printf("1-LISTA SIMPLESMENTE ENCADEADA SEM NO CABECA(ORDENADA)\n");
        printf("2-LISTA CIRCULAR SIMPLESMENTE ENCADEADA SEM NO CABECA(ORDENADA)\n");
        printf("3-LISTA DUPLAMENTE ENCADEADA COM NO CABECA(ORDENADA)\n");
        printf("4-FILA(FIFO)\n");
        printf("5-PILHA(LIFO)\n");
        printf("6-SAIR\n--->");
        scanf("%d",&op);
        
        switch (op){
            case 1:
                MENUSIMPLES();
            break;
            case 2:
                MENUCIR();
            case 3:
                MENUSDUPLA();
            break;
            case 4:
                MENUFILA();
            break;
            case 5:
                MENUPILHA();
            default:
                if(op!=6){
                    printf("OPCAO INVALIDA\n\n");
                }
        }
    }
	return 0;
}
