#include<iostream>

// Private : pode acessar informações somente na classe, não é acessivel via objeto ; exemplo t1.area() é via objeto (dados privados)

// Public : pode acessar informaçoes dentro da classe e via objetos (dados publicos)

// O acesso a dados de membros privados, via objeto, é proibido. Assim , para acessarmos esses dados, definimos procedimentos publicos
// denominados Geters("pegador") e Seters ("setador")

//Construtores: uma função com o mesmo nome da classe, usado para que no momento que for criado o objeto, seja inserido
// um valor nele;

//Destrutor: uma função que invoca automaticamentee (sem parametros) , com uma finalidade de encerrar o objeto 

using namespace std;

class DTriangulo{
    float base, height;

    public:
        DTriangulo(){       // Construtor
            base = height = 1; // Todo objeto criado tera o valor 1
        }

        float getBase(){  // Geter da base
            return base;
        }
        float getHeight(){  // Geter do height
            return height;
        }

        void setBase(float base){   // Set da base
            this->base = base;
        }
        void setHeight(float height){ // Set do height
            this->height = height;      // this->height = ponteiro para a vareavel privado, recebe o valor do height do Seter
        }

        ~DTriangulo(){      // Destrutor
            cout<<"Destrutor"<<endl; // Teste de vereficação do funcionamento
        }

};

int main(){
    DTriangulo t1;

    cout<<"Base: "<<t1.getBase()<<endl;
    cout<<"Height: "<<t1.getHeight()<<endl;




    return 0;
}