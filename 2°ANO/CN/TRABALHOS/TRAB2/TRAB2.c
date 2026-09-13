#include<stdio.h>
#include<string.h>
#include<time.h>

// Cálculo de determinante pelo método de Gauss com pivotação parcial
//Entrada: o ordem da matriz (Máximo 10)  ,  a Matriz

//Saída: o Resultados de cada passo com 1 casa decimal ,  o Determinante,   o Tempo de execução

float GLOBAL[10];

// PROCEDIMENTO PARA IMPRIMIR OS VALORES DA MATRIZ
void imprima(float matriz[], int x){
    
        printf("|  ");
        for(int j =0;j<x;j++)
            printf("%0.1f   ",matriz[j]);
        printf("|\n");
}

//FUNÇÃO PARA CALCULAR A MATRIZ 
void ZERARM(float m[], float zero, int x, float g[]){
    for(int i=0;i<x;i++){
        GLOBAL[i]=g[i]*zero+m[i];
    }
}



int main(){
    int x, y, i, j, PIVO, c=0, inv=0;
    float M=-999, k, zero, det=1;
    float matriz[10][10];
    float AUX[10];

    clock_t inicial, final;
    inicial = clock();
    printf("INSIRA A QUANTIDADES DE LINHAS E COLUNAS (NESSA ORDEM)\n");
    scanf("%d %d",&x, &y);
    printf("INSIRA OS VALORES DA MATRIZ\n");
    for(i=0;i<x;i++){
         for(j =0;j<y;j++){
            scanf("%f",&matriz[i][j]);
        }
    }

    printf("\n\nMATRIZ INICIAL: \n");
    for(i=0;i<x;i++){
        imprima(matriz[i],y);
    }


    do{
        // ACHAR O PIVO 
        for(i=c;i<x;i++){
            k = matriz[i][c];
            if(k<0)
                k = k*-1;
            if(k>M){
                M = k;
                PIVO = i;
            }
        }

        //CONDIÇÃO CASO TENHA QUE INVERTER ALGUMA LINHA 
        if(PIVO!=c){
            inv++;
            for(i=0;i<x;i++){
                AUX[i]= matriz[c][i];
                matriz[c][i] = matriz[PIVO][i];
                matriz[PIVO][i] = AUX[i];
            }

            printf("-----------------------------------------------\n\n");
            printf("INVERTER A LINHA (%d) PELA  (%d)\n",PIVO+1, c+1);
            for(i =0;i<x;i++){
                imprima(matriz[i],y);
            }
        }
        
        // FAZER O CALCULO PARA ZERAR AS LINHAS 
        for(i =c+1;i<x;i++){
            zero = -(matriz[i][c]/matriz[c][c]);
            ZERARM(matriz[i],zero,x,matriz[c]);
        
            for(j=0; j<x; j++){
                matriz[i][j] = GLOBAL[j]; 
            }
        }


        printf("-----------------------------------------------\n\nMATRIZ RESULTANDO DEPOIS DO CALCULO: %d\n",c+1);
        for(i =0;i<x;i++){
            imprima(matriz[i],y);
        }
        c++;
        M=-9999;

    }while(c<x-1);
   
 
    printf("-----------------------------------------------\nMATRIZ FINAL\n\n");
    for(i =0;i<x;i++){
        imprima(matriz[i],y);
    }

    //CALCULAR O DETERMINATE 
    for(int i=0; i<x;i++)
        det = det*matriz[i][i];
    
    if(inv%2!=0){
        det = det*-1;
    }
    //VERIFICAR SE É UMA MATRIZ QUADRADA 
    if(x==y){
        printf("\nDETERMINANTE: %0.1f\n\n",det);
    }else{
        printf("\nNAO POSSUI DETERMINANTE POR NAO SER UMA MATRIZ QUADRADA\n\n");
    }


    final=clock();
    printf("\nTempo de execucao:%f",(double)(final-inicial)/CLOCKS_PER_SEC);
    return 0;
}
