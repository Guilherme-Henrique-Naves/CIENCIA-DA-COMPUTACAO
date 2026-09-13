#include<iostream>

using namespace std;


// int i = 'a'  --> i = 97 ,  casting implicito


// int i = (int)'a'  --> i = 97 . casting explicito 
class DTCelcius{
    double temperatura;

    public:

    DTCelcius(const int &i=0) : temperatura(i){}  // t=i , converção do i para t

    operator double()const{
        return temperatura;  // i = t , conversão do t para int 
    }



   double getTemp(){
        return temperatura;
    }
 
};

class DTFahre{
    double temperatura;

    public:


    DTFahre(const int &i=0) : temperatura(i){} 

    
    
    DTFahre(const DTCelcius &c){  // DTCelsius para acessar o objeto da classe DCelcius , 'c' recebe os valores do objeto
                                 // função para converter celcius para fahre
        temperatura = c*9/5+32; // o obj c passa por csting para int 

    }



    operator DTCelcius()const{        // operator para converter fahre para celcius
        return (temperatura-32) *5/9;
    }

     double getTemp(){
        return temperatura;
    }

};

int main(){
    DTCelcius c(10), c1;
    DTFahre  f(50), f1;

    c1 = f;

    f1 = c;

    cout<<"CELCIUS: "<<c1.getTemp()<<endl;
    cout<<"fahre: "<<f1.getTemp();

    return 0;
}