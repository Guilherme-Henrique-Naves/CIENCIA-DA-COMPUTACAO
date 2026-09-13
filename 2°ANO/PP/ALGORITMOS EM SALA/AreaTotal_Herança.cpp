#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


class DFigs{
    public:
        virtual float calcArea() = 0;  // virtual : indica que a função pode ser sobrescrita em classes derivadas e retornar o valor 
};

class DQuad : public DFigs{
    float l;

    public:
        DQuad(float l=1.0) : l(l){}

        virtual float calcArea(){ 
            return l*l;
        }

};


class DTriang : public DFigs{
    float b, h;

    public:
        DTriang(float b=1.0, float h=1.0) : b(b), h(h){}

        virtual float calcArea(){
            return b*h/2.0;
        }

};



class DCircunf : public DFigs{
    float r;

    public:
        DCircunf(float r=1.0) : r(r){}

        virtual float calcArea(){
            return M_PI * pow(r,2);
        }

};


/*
// Função usando apenas vector
class DConjuntosGeometrico : public vector<DFigs*>{   // Usa o vector para guarda os valores em um vetor

    public:
        float areaTotal(){
            float AreaTotal=0.0;
            int i;

            for(i=0; i<size(); ++i ){    // size()  --> Tamanho do vector
                AreaTotal += at(i) -> calcArea();   // at(i) --> posição i do vector
            }
        }
};
*/


// Unsando o " INTERATOR " para somar a area
class DConjuntosGeometrico : public vector<DFigs*> {  

    public:
        float areaTotal(){
            
           vector<DFigs*> :: iterator it; // declaração do interator
            float AreaTotal=0.0;
            
            for(it=begin();it!=end();++it){       // begin() ---> ponteiro que aponta para o começo do interator
                AreaTotal += (*it) -> calcArea();   //  end() --> ponteiro que aponta para o final do interator
            }
            return AreaTotal;
        }
};


int main(){
    
    // Procedimento usando a class "DConjuntosGeometricos"
    DConjuntosGeometrico VPFigs;
    
    
    float AreaTotal = 0.0;

    VPFigs.push_back(new DQuad);
    VPFigs.push_back(new DTriang);
    VPFigs.push_back(new DCircunf);

    cout<<VPFigs.areaTotal()<<endl;

    /*______________________________________________________________________________________________
        // Procedimento sem usar a class "DConjuntosGeometricos"
        DFigs *V[3];  // Vetor de ponteiros
        float AreaTotal;
        int i, n;
        
        
        V[0] = new DQuad;      // Obs --> para colocar valores na função : DQuad(x); x = elemento inserido
        V[1] = new DTriang;
        V[2] = new DCircunf;

        for(i=0, n=3; i<n; ++i ){
            AreaTotal += V[i] -> calcArea();
        }

        cout<<AreaTotal<<endl;
*/        
    return 0;
}