#include<iostream>


using namespace std;

// OBJETIVO : GUARDAR E IMPRIMIR OS ELEMENTOS DO VETOR


class DArrayOpIndex{
    int V[10];

    public:

    // OPERADOR [] -> USAMOS SOBRECARGA DE OPERADORES PARA CONSEGUIR ACESSAR OS ELEMENTOS DE CADA POSIÇÃO DO VETOR
    int& operator [](unsigned index){ //"int&" -> NECESSARIO PARA GUARDAR VALORES NO VETOR 

        return V[index];   // RETORNA O ELEMENTO GUARDADO NA POSIÇÃO " INDEX" NO VETOR "V"
    }


};

int main(){
    // TESTANDO COM INTEIROS---------------------------------------------------------
    DArrayOpIndex A;
    int i;


    // COLOCANDO VALORES NO VETOR
     for(i=0;i<10;i++){
        A[i] = i;     
    }
  

    // IMPRIMINDO OS VALORES
    for(i=0;i<10;i++){
        cout<<A[i]<<' ';
    }

    return 0;
}