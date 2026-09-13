#include <stdio.h>
#include <math.h>
#include<time.h>


float cal(float b, float ans, int p, int cont){
    float parada =b;

    b = b-((pow(b,p)-ans)/(p*pow(b,p-1)));
    printf("INTERACAO[%d] = %f \n",cont,b);
    
    if(b!=parada)
        return cal(b,ans,p,cont+1);

    if(b==parada)
        return printf("\n\n RESULTADO = %f",b);
    
}


int main(){
    float p;
    int m;
    
    printf("Valor de P:");
    scanf("%f",&p);

    printf("Valor de M: ");
    scanf("%d",&m);

    clock_t inicial, final;
    inicial=clock();
    
    cal(1,p,m,0);

    final = clock();

    printf("\nTempo de Execucao:%.7f",(double)(final-inicial)/CLOCKS_PER_SEC);

    


}