#include<iostream>
#include<math.h>
#include<cmath>

using namespace std;


// Tarefa feita por mim em sala
class Circulo{
    float area, circun, raio;

    public:
        
        // raio padrão como 1
        Circulo(){
            raio = 1;
        }

    
        // função para calcular area
        float Area(){
            area = raio*raio*M_PI;  //obs: M_PI ---> atua como valor de PI
            return area;
        }

        //função para calcular a circuferencia
        float Circun(){
            circun = 2*raio*M_PI;
            return circun;
        }

};

int main(){

        Circulo c1;

        cout<<"Area: " << c1.Area() << endl;
        cout<<"Circunferencia: "<<c1.Circun()<<endl; 

    return 0;
}