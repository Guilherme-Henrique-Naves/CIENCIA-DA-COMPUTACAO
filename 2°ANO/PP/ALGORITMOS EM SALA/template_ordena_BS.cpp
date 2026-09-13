#include <iostream>

using namespace std; // usado para facilitar o uso da função std ( não precisa usar o "std::");

// unsigned : definir apenas numeros positivos;
// long : dobra aquantidade de bits 
//short : quebra os bits pela metade(obs: não funciona com char) para economia de memoria
 
 
 // Ordenar em Bubble Sort : compara elementos adjacentes e os troca se estiverem fora de ordem.
 // MEU CODIGO
 template<typename T>
void ordenaM(T v[], unsigned n ){ 
    T temp, i, j;
    for(j=0;j<n;j++){
        for(i=0;i<n;i++){
            if(v[i]>v[i+1]){
                temp = v[i];
                v[i]= v[i+1];
                v[i+1] = temp;
            }
        }
    }
}

//CODIGO DO PROFESSOR
template<typename T>
void ordenaP(T V[], unsigned n){
    unsigned i,j,aux,menor;
    for(i=0;i<n-1;i++){
        menor =i;
        for(j=i+1;j<n;++j)
            if(V[menor]>V[j])
                 menor = j;
        aux = V[i];
        V[i]=V[menor];
        V[menor]= aux;      
    }
}

//CODIGO DO PROFESSOR com ponteiro
template<typename T>
void ordenaPP(T V[], unsigned n){
    T *pi,*pj,aux,*pmenor;
    for(pi=V;pi<V+(n-1);++pi){
        pmenor =pi;
        for(pj=pi+1;pj<V+n;++pj)
            if(*pmenor>*pj)
                pmenor = pj;
        aux = *pi;
        *pi=*pmenor;
        *pmenor= aux;
            
    }
}
int main(){
    int VM[]= {3,1,6,8,4,9};
    int VP[]= {3,1,6,8,4,9};
    int VPP[]= {3,1,6,8,4,9};
    int i;

    ordenaM(VM,6); // função para ordenar usando o "meu codigo";
    ordenaP(VP,6); // função para ordenar usando o "codigo do professor";
    ordenaPP(VPP,6); // função para ordenar usando o codigo do "professor com ponteiro";

    for(i=0;i<6;i++){
        cout<<VM[i]<<" ";
    }
    cout<<endl;
      for(i=0;i<6;i++){
        cout<<VP[i]<<" ";
    }
     cout<<endl;
      for(i=0;i<6;i++){
        cout<<VPP[i]<<" ";
    }
    cout<<endl;
    return 0;
}