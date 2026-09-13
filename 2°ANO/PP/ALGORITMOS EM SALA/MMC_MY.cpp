#include<iostream>

using namespace std;


// CODIGO FEITO POR MIM (TAREFA EM SALA) -----------------------------------------------------------
class DFrac{
    int x,  // NUMERADOR 
        y; // DENOMINADOR

public:

        DFrac(int x=0, int y=1): x(x), y(y){} // CONSTRUTOR

        int getX(){
            return x;
        }
        int getY(){
            return y;
        }

        // MMC DOS NUMERAROES
       DFrac MMC(DFrac  &other){
            int x1 =x;        // x = atribustos do "P1";
            int x2 = other.x; // other.x = atribustos do "P2";

            int cont =1, i=2;
            while(x1>1 || x2>1){
                
                if(x1%i==0 || x2%i==0){
                    if(x1%i==0){
                        x1 = x1/i;
            
                    }
                    if(x2%i==0){
                        x2 = x2/i;
                    }
                    
                    cont = cont*i;
                       
                }else{
                    i=i+1;
                }

            }
        
           return DFrac(cont,0); // RETORNAR A FUNÇÃO CONSTRUTOR PARA RECEBER OS VALORES
        }


        // SOMA DE FRAÇÃO
        DFrac SomaFra(DFrac &other){
            int dem, num;

            num = x*other.y;
            num = num+ y*other.x;
            dem = y*other.y;

            return DFrac(num,dem);
        }





// CODIGO FEITO PELO PROFESOR PARA SOBRECARGA DE OPERADORES----------------------------

        // SOBRECARGA DE OPERADOR +
        DFrac operator+ (const DFrac &other){
            
            return DFrac(x*other.y+y*other.x,y*other.y);
        }
        


        //SOBRECARGA DO OPERADOR < ( RETORNA UM VALOR BOOLEANO)
        bool operator<(const DFrac &other)const{        
            return (x*other.y-y*other.x)<0;
        }

        //TAREFA IMPRELMETA * ,/ ,- , <= , >= , >   

//FEITA POR MIM ( TAREFA) -----------------------------------------------------------------------


        // OPERADOR -
        DFrac operator- (const DFrac &other){
            return DFrac(x*other.y-y*other.x,y*other.y);
        }


        // OPERADOR -
        DFrac operator / (const DFrac &other){
            return DFrac(x*other.y/y*other.x,y*other.y);
        }


        //OPERADOR *
        DFrac operator* (const DFrac &other){
            return DFrac(x*other.x,y*other.y);
        }

        //OPERADOR <=
        bool operator<= (const DFrac &other){
           return (x*other.y-y*other.x)<=0;
        }


        // OPERADOR >=
        bool operator>= (const DFrac &other){
            return (x*other.y-y*other.x)>=0;
        }
        
        // OPERADOR >
        bool operator> (const DFrac &other){
           return (x*other.y-y*other.x)>0;
        }

        // OPERADOR ++
        DFrac operator++ (){ // PRÉ FIXADO  ++A
            x = x+y;
            return DFrac(x,y);
        }


        // OPERADOR ++
        DFrac operator++ (int){ // PÓS FIXADO  A++
         DFrac aux(x,y);
         x=x+y;
         return aux;


        }

};


void MEU(){
    DFrac p1, p2(1,2), p3(1,3);  // P1( NUMERADOR, DENOMINADOR)
    bool b;

   //p1 = p3.MMC(p2); ->    CALCULAR O MMC

    b = p2<p3; // VALOR BOOLEANO 
    

    if(b){    // VERIFICAR O FUNCIONAMENTO 
        printf("\nVERDADEIRO");
    }else{
        printf("\nFALSO\n");
    }


    
    b = p2>p3; // VALOR BOOLEANO 
    

    if(b){    // VERIFICAR O FUNCIONAMENTO 
        printf("\nVERDADEIRO\n\n");
    }else{
        printf("\nFALSO\n");
    }

      p1 = p2++; // POS FIXADO 

    cout<<"P2:  "<<p2.getX()<<"/"<<p2.getY()<<endl;
    cout<<"P1:  "<<p1.getX()<<"/"<<p1.getY()<<endl;

}

void PROF(){
    DFrac p1, p2(1,2), p3(1,3);  // P1( NUMERADOR, DENOMINADOR)
    
    //p1 = p2*p3;  // OPERAÇÃO DE FRAÇÃO USANDO SOBRECARGA DE OPERADORES (CODIGO DO PROFESSOR)
    p1 = p2++;

    cout<<p2.getX()<<"/"<<p2.getY()<<endl;
    cout<<p1.getX()<<"/"<<p1.getY()<<endl;

}



int main(){
    MEU();   //-> MEU CODIGO

  // PROF(); // -> CODIGO DO PROFESSOR



    }