#include <iostream>
#include<memory>

using namespace std;

// Fazendo o P2 alterar o valor do P1
void Mudar_Valor(){

    int *p1 = new int;
    *p1=10;
    
    int *p2 = p1; // o endereço de P2 recebe o P1

    *p2=10; // Alterei o valor de P1 usando o P2
    
    cout<<"P1: "<<*p1<<endl;
}

// TEMPLATES DE PONTEIROS "INTELIGENTES"
// unique_ptr : ponteiro unico , p1-> O    p2-> O , cada um aponta para um determinado endereço
// shared_ptr : ponteiro compartilhado  p1-> O  <- p2 , ambos apontam para o mesmo endereço .Caso um deles sejam desalocados, ambos serão

void SHARED(){

    shared_ptr<int> p1 (new int); // Para usar o shrared , necessita da biblioteca memory
    *p1=10;
    shared_ptr<int>p2=p1;
    *p2=5;
    cout<<"P1: "<<*p1<<endl;
    p1.reset(); // Atua como o delete , mas não delete o P2 
    *p2 = 6; 
    cout<<"P2: "<<*p2<<endl;
}


int  main(){
    cout<<"MUDAR VALOR"<<endl;
    Mudar_Valor();

    cout<<"SHARED"<<endl;
    SHARED();
    return 0;
}