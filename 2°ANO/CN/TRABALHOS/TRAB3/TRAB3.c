#include<stdio.h>
#include<string.h>
#include<time.h>

//Resolução de sistemas lineares pelo método de Gauss-Seidel
// Entrada: o ordem da matriz (máximo 10) dos coeficientes das incógnitas, Sistema linear, Precisão,  Solução inicial

//Saída: Resultados de cada passo (sistema e erro) com 7 casas decimais, Solução, o Tempo de execução 


float calculo(float matriz[], int i, float inic[], int x){
    float  k= 1/matriz[i];
    float result=matriz[x]*k;
    for(int j=0; j<x; j++){
        if(j!=i){
            result = result+k*(matriz[j])*inic[j];
        }
    }
    return result;
}


int main(){
    int x, y, i, j, l=1;
    float matriz[10][10], maiornum=0, maiordom=0, invert, dr, E=0;
    float inici[10];
    float inici2[10];
    clock_t final, inicial;
    inicial=clock();

    printf("\nINSIRA A QUANTIDADES DE LINHAS E COLUNAS (NESSA ORDEM)\n");
    scanf("%d %d",&x, &y);

    printf("\nINSIRA A MATRIZ: ");
    for(i=0;i<x;i++){
         for(j =0;j<y;j++){
            scanf("%f",&matriz[i][j]);
            if(j<y-1 && i!=j){
                matriz[i][j] = matriz[i][j]*-1;
            }
        }
    }
    printf("\n\nINSIRA A SEQUENCIA INICIAL: ");
    for(j =0;j<x;j++){
        scanf("%f",&inici[j]);
    }
    printf("\n\nINSIRA A PRECISAO: ");
    scanf("%f",&E);

  
   
    do{
        printf("\nSOLUCAO----------------\n");
        for(i=0;i<x;i++){

            inici[i] = inici2[i];
            inici2[i]=calculo(matriz[i],i, inici2, x);
            printf("\nX= %f=",inici2[i]);
            invert = inici2[i];

            if(invert<0){
                invert = invert *-1;
            }
            if(invert>maiornum){
                maiornum = invert;
            }
        }
        printf("\n");
        for(i=0;i<x;i++){
            invert = inici2[i]-inici[i];
            if(invert<0){
                invert = invert*-1;
            }
            if(maiordom<invert){
                maiordom=invert;
            }
        }
            printf("\n%0.7f / %0.7f\n",maiordom,maiornum);
        dr=maiordom/maiornum;

        printf("\nDR[%d]== %0.7f\n",l,dr);
        maiordom=0;
        maiordom=0;
        l++;
    }while(dr>E);
    final = clock();
    printf("\nTempo de execucao: %f",(double)(final-inicial)/CLOCKS_PER_SEC);
        return 0;
}