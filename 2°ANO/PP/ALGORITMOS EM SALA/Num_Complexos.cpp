#include<iostream>



using namespace std;

class DNComplexos{
    float a, b;

public:
    DNComplexos(float a=1, float b=1):a(a), b(b){}


    float getA(){
        return a;
    }
    float getB(){
        return b;
    }


    // função para somar dois objetos(forma não convencional)
    DNComplexos soma(const DNComplexos &other) const{ // usando ponteiro para acessar o valor de outro objeto

        return DNComplexos(a+other.a,b+other.b);  // explicação : "a" e "b" atua os valores do objeto "c2"
                                                 //               "other.a" e "other.b" atua os valores do objeto "c3"
    }


   //função para somar dois objetos(forma convencional)
    DNComplexos operator +(const DNComplexos &other) const{   //obs: operator--> necessario para sobrecarga de operadores
        return DNComplexos(a+other.a,+b+other.b); // retorna o resultado da soma entre dois objetos na vareavel "c1"
    }


};

//Procedinento para entender como funciona contas matematicas de dois objetos
void OperadorBasico(){
    DNComplexos c1, c2, c3;

    c1 = c2.soma(c3);

    cout<<"a="<<c1.getA()<<" b= "<<c1.getB()<<endl;

}


// procedimento ideal para contas matematicas entre dois objetos usando a sobrecarga  de operadores
void OperadorIdeal(){
    DNComplexos c1, c2, c3;

    c1 = c2+c3;

    cout<<"a="<<c1.getA()<<" b="<<c1.getB()<<endl;


}

int main(){

    OperadorBasico(); // modelo basico

    OperadorIdeal();// modelo ideal
    return 0;
}