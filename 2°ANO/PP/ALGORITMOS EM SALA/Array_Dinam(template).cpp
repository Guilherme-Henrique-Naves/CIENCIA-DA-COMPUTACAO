#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<memory>


using namespace std;

template <class T>
class DDinamincArray{
    unique_ptr<T> v;   // Acessar dinamicamente
    unsigned arraysize;

public:

    //CONSTRUTOR : iniciar o "arrayzise" como 10 (limite do array) e determinar o tamanho do 
    // "V" em 10
    DDinamincArray(unsigned arraysize =10): arraysize(arraysize), v(new T[arraysize]){}


    // DESTRUTOR: desalocar a posição do array(vetor)
    // não precisa 


    // Procedimento caso tenha que alterar o tamanho do array(vetor)
    void reserve(unsigned newarray){
        unique_ptr<T> vaux;

        if(newarray ==0) throw string("Tamanho invaçido"); // O valor do array tem que ser no mínimo 1

        vaux.reset(new T);
        
        //copiar o conteudo do "V para" o "Vaux"
       memcpy(vaux.get(),v.get(),sizeof(T)*(arraysize < newarray ? arraysize : newarray)); // verificar se o arraysize é menor que o newarray

        v.swap(vaux);
        arraysize = newarray;
    }

    unsigned GetArray() const{
        return arraysize;
    }

    T GetDD(unsigned i)const{
        if(i>=arraysize){                     //i não pode ser maior que o tamanho total do vetor 
        throw string("Acesso invalido de memoria"); //Caso seja maior(Exceção) que 10, o "THROW" vai encerrar a função 
        }else{
            return *(v.get()+1);
        }
    }

    void SetDD(unsigned i, T element)const{
        if(i>=arraysize){                     //i não pode ser maior que o tamanho total do vetor 
        throw string("Acesso invalido de memoria"); 
        }else{
            *(v.get()+1) = element;
        }
    }

    /* 
        Uma alternativa "Não muito convecional" para acessar a posição de um array(vetor)
        int* getV(){
            return v;
    }
    */

};



// Função para demostrar como funciona a operação usando string 
 void stringTest(){  // precisa do "include<string>" para funcionar

    string s1, s2("algo "), s3("outro ");
    
    s1=s2+"teste "+s3;  // objetivo: somar os caracteres de s2 + "teste" + s3 , e guardar em s1  

    cout<<s1<<endl;  // resultado: "algo teste outro", 

    s1[1] = 'u'; // trocar o valor da posição 1 do vetor por 'u';

    cout<<s1<<endl;  // resultado: "augo teste outro",

 }

 void FDDinamicArray(){

    DDinamincArray<int> DA(2);
    int i;

    for(i=0;i<DA.GetArray();i++){
        DA.SetDD(i,0);
    }
    DA.reserve(4);

    for(i=0; i<DA.GetArray();i++){
        cout<<DA.GetDD(i)<<" ";
        DA.SetDD(i,1);
    }

    cout<<endl;

    DA.reserve(2);

    for(i=0;i<DA.GetArray();i++){
        cout << DA.GetDD(i)<<" ";
        DA.SetDD(i,1);
    }
    DA.reserve(4);

    cout<<endl;




    /*Verificar o funcionamneto do THROW
    try{
        cout<<DA.GetDD(11)<<endl; // Objetivo : atingir a excecão para encerrar a função 
    }
    catch(string c){
       cout<<c<<endl; // O valor encerrado no "THROW", pode ser guardado para a proxima função
    }
    
    cout<<"Passou da exeption"<<endl;
*/


    
   /*Caso tenha usado o método alternativo 
    
    
    DDinamincArray DA;
    
    DA.getV()[1]=9; // Guarda "9" na posição 1 do vetor DA

    cout<<DA.getV()[1]<<endl; // imprimir apenas a posição 1 do vetor 
    */

 }
int main(){

    //stringTest();  
    FDDinamicArray();

    return 0;
}