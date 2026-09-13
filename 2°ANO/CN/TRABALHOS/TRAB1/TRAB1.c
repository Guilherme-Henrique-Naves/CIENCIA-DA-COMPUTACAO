#include <stdio.h>
#include <math.h>
#include<time.h>

// FUNÇÃO PARA CALCULAR O FATORIAL 
int fat (int exp){
  if(exp == 0){
	  return 1;
	}
  return exp * fat (exp - 1);

}

int main (){
  int x, exp = 2;
  float res = 1;
  float r;

  clock_t inicial, final;

  inicial=clock();

  printf ("\nINSIRA O VALOR EM GRAUS: ");
  scanf ("%d", &x);

  //CONVERSÃO PARA RADIANOS
  r = ((x*3.14159265359)/180);


  //LOOP PARA FAZER O CALCULO COM 10 TERMOS
  for(int i = 1; i <= 10 - 1; i++){
	  if(i%2!=0){
      res = res + ((-1)*(pow(r,exp)/fat(exp)));
    }else{
      res = res +(pow(r, exp)/fat(exp));
    }
    exp = exp + 2;

	}

  printf ("COS(%d): %.9f\n\n", x, res);
  final = clock();

  printf("\nTempo de execucao:%.7f",(double)(final-inicial)/CLOCKS_PER_SEC);

  return 0;
}
