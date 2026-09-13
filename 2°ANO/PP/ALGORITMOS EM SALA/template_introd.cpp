#include<iostream>


template <typename T> // template <typename T, typename U>, método para o uso de dois tipos;

T funcao(T a, T b){  // pode ser usado como T funcao(T a, U b), quando usado mais de um tipo;
    return a+b;     // funcao<int,float>(i,j), exemplo para o uso da função; 
}

int main(){

    int i, j;

    std::cin >>i;   // "std ::" usado para acesar o função "cin";
    std::cin >>j; // cin : extrair o que digitar no teclado e guardar na varieavel;



    std::cout<<funcao<int>(i,j)<<" "<<funcao<float>(i,j);     // cria uma função int no "funcao";
                                                             // cout : atua como o printf ;
                                                             // cria uma função float no "funcao";

    return 0;
}