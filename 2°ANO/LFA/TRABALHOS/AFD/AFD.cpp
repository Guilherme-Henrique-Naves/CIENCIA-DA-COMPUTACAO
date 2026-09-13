
//TRABALHO: FAZER UM AUTÔMATO E VERIFICAR SE A PALAVRA É ACEITA 



#include <stdio.h>
#include <string.h>

#ifdef __unix__
    #include <unistd.h>
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32)

   #define OS_Windows

   #include <windows.h>

#endif


#define TRAVOU 'x'

char global [30][10]; // VAREAVEL GLOBAL PARA GUARDA OS VALORES DO DELTA


//FUNÇÃO PARA RECEBER SEPARACÃO COM VIRGULA
void gets(char *str, int t, int *tamW){
     fgets(str,t,stdin)-1;  //coloca \n e \0 no fim
     *tamW=strlen(str)-1;
     str[*tamW]='\0';        //'\0' no lugar de '\n'
}


//FUNÇÃO PARA SEPARAR 
void split (char *Q, char *str, char sep, int *tam)
{
    int i,j=0;
    for(i=0;i<*tam;i++)
        if (str[i]!=sep)    //se nÃo encontrou o separador
            Q[j++]=str[i];
    *tam = j;               //guarda o tamanho dos elementos

}



// FUNÇÃO PARA DEFINIR OS VALORES DO DELTA

void Delta(char d[], char alfabeto[], char estados[], int c){
    int i;
    for( i=0;i<strlen(alfabeto);i++){
        printf("Delta(%c,%c)= ",estados[c], alfabeto[i]);
         scanf("%s",&d[i]);         
    }
}


//FUNÇÃO PARA DEFINIR SE A PALAVRA É ACEITA 
char LFD(char ini[], char ace[], char word[], char alfabeto[], char estados[], int cont){
    int i=0, j=0, k, aceita=0;
    char atual[0];
   if(cont<=strlen(word)){
        for(i=0;i<strlen(estados);i++){ 
            if(ini[0] == estados[i]){
                for(j=0;j<strlen(alfabeto);j++){
                    if(word[cont]==alfabeto[j]){
                        atual[0]=global[i][j];
                        return LFD(atual,ace,word,alfabeto,estados,cont+1); // RECURCIVIDADE PARA PERCORRER A PALAVRA VERIFICADA
                    }
                }
            }
        }
    }
    for(k=0;k<strlen(ace);k++){ 
        if(ini[0]==ace[k])          // CONDIÇÃO SE SE A PLAVRA FINAL FOR IGUAL AO ESTADO ACEITAVEL
            aceita=1;
    }
    
    if(aceita==1){
        printf("\nPALAVRA ACEITA\n");
    }else{
        printf("\n PALAVRA REJEITADA");
    }

}

int main(){
    
    char str[30];
    char inicial[1];
    char aceitav[30], aceita[10], aceiv[10], test[10];
    char palavra[20];
    char alfav[10], alfa[10];
    char estav[10], esta[10];
    int i, j, tamQ, tamj;
    char a[1], conti[1];
    
    do{
        // guardar o ALFABETO 
        printf("\n\nEntre com o conjunto de ALFABETO, separados por virgula : ");
        gets(str,30,&tamQ);   
        split(alfav,str,',',&tamQ);             // split para tirar a separação de virgula
        split(alfa,alfav,' ',&tamQ);            // split para tirar a separação de espaço

        
        //GUARDA O ESTADO
        printf("Entre com o conjunto de ESTADO, separados por virgula : ");
        gets(str,30,&tamQ);
        split(estav,str,',',&tamQ);             // split para tirar a separação de virgula
        split(esta,estav,' ',&tamQ);            // split para tirar a separação de espaço
        
        // GUARDA OS ESTADOS EACEITAVEIS
        printf("Entre com os estados ACEITAVEIS, separados por virgula: ");
        gets(str,30,&tamQ);
        split(aceiv,str,',',&tamQ);             // split para tirar a separação de virgula
        split(aceita,aceiv,' ',&tamQ);          // split para tirar a separação de espaço
        for(i=0;i<strlen(aceita);i++)
            test[i]=aceita[i];
        
        
        // GUARDA O INCIAL
        printf("Entre com o estado INICIAL: ");
        gets(inicial,30,&tamQ);

        
        char d[strlen(esta)][strlen(alfa)];


        //GUARDA OS VALORES DO DELTA EM UMA MATRIZ
        for(i=0;i<strlen(esta);i++){
            Delta(d[i],alfa,esta,i);  
        }
        
        
        //PASSA OS VALORES DO DELTA PARA UMA MATRIZ GLOBAL
        for( i=0;i<strlen(esta);i++){
            for( j=0;j<strlen(alfa);j++){
                global[i][j] = d[i][j];
            }
        }
        
        
        // GUARDA A PALAVRA A SER VERIFICADA
        do{
        printf("\nEntre com a palavra a ser VERIFICADA: ");
        scanf("%s",palavra);
        scanf("%*c");

        LFD(inicial,test,palavra,alfa,esta,0);  // FUNÇÃO PARA VERIFICAR SE A PALAVRA É ACEITA
        
       
        //VERIFICAR OUTRA PALAVRA NO MESMO AUTOMOTO AUTÔMATO
        printf("\n\nDESEJA ENTRAR COM OUTRA PALAVRA PARA SER VERIFICADA?( DIGITE 1 PARA SIM): ");
        scanf("%s",conti);
        scanf("%*c");
        
        
        }while(conti[0]=='1');
        
        //CONTINUAR COM AUTÔMATO DIFERENTE
        printf("\n\nDESEJA CONTINUAR COM UM NOVO AUTÔMATO?(DIGITE  s   ou   S  para SIM): ");
        gets(a,30,&tamQ);

    }while (a[0]=='S' || a[0]=='s');
      
    return 0;
}