#include <iostream>
#include <cmath>

using namespace std;

class SOLIDOS{
    public:
    virtual float calcArea() = 0;
    virtual float calcVolume() = 0;



};

class Esferas : public SOLIDOS{
    float r;

    public:

        Esferas(float r=1): r(r){}

        virtual float calcArea(){
            return  4*M_PI*pow(r,2);
        }

        virtual float calcVolume(){
            return (4.0/3.0)*M_PI*pow(r,3);
        }

};

class CILINDROS : public SOLIDOS{
    float r, h;

    public:

        CILINDROS(float r=1, float h=1): r(r), h(h){}

        virtual float calcArea(){
            return  2*M_PI*pow(r,2) + (2*M_PI*r*h);
        }

        virtual float calcVolume(){
            return M_PI*pow(r,2)*h;
        }


};



int main(){



        SOLIDOS *E[6];  // Vetor de ponteiros
        float AreaTotal = 0.0, VoluTotal = 0.0;
        int i, n;
        
        
        E[0] = new Esferas(3);      
        E[1] = new Esferas(3);
        E[2] = new Esferas(3);
        E[3] = new CILINDROS(3);      
        E[4] = new CILINDROS(3);
        E[5] = new CILINDROS(3);

        for(i=0, n=6; i<n; ++i ){
            AreaTotal += E[i] -> calcArea();
            VoluTotal += E[i] -> calcVolume();
        }

        cout<<"Area total ESFERA: "<<AreaTotal<<endl;
        cout<<"Volume total ESFERA: "<<VoluTotal<<endl;


}