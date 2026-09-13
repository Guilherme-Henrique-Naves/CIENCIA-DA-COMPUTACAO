#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template <class T>

class DStack{
    unique_ptr<T> ptr; 
    unsigned topIndex;
    unsigned capacity;

    // procedimento para caso seja necessario alterar o tamanho do array(vetor)
    void reserve(unsigned capacity){
        unique_ptr<T> pAux;

        //verificar se o novo capacity é maior que 0
        if(! (capacity>0))
            capacity = 1;

        //alocar novo array(vetor) em pAux
        pAux.reset(new T[capacity]);

        //copiar o array(vetor) de ptr para pAux
        memcpy(pAux.get(),ptr.get(),topIndex * sizeof(T));

        //fazer ptr apontar para pAux
        ptr.swap(pAux);
        this->capacity = capacity;
    }

public:
    DStack(unsigned capacity = 2):
        topIndex(0), // vareavel para saber a quantidade de elementos na pilha
        capacity(capacity), // vareavel para determinar a capacidade maxima da pilha 
        ptr(new T[capacity]) // vareavel vetor com o tamanho maximo que definimos em "capacity"
        {}
   
   
    // função para retorna o elemento que esta no topo da pilha ( atua como printf)
    T top() const{
        return *(ptr.get()+topIndex-1);  // obs: get() --> necessario para acessar o array(vetor) de ptr
                                        //      +topIndex --> necessario para determinar a posição do vetor

    }



    //procesimento para inserir elemento no topo da pilha
    void push(T elem){
        //se a pilha esta cheia, então alocar mais espaço(aumentar o tamanho da pilha) para inserir novo elemento
        if(capacity == topIndex)
            reserve(capacity*2);

        //inseri elementos
        *(ptr.get()+topIndex) = elem;
        ++topIndex;  // necessario para sabermos a quantidade de elementos  na pilha
    }
      
    
    // função para remover elementos da lista
    bool pop(){
        //se pilha vazia então retorne falso
        if(topIndex == 0)
            return false;

        // se ouver elementos remove o elemento do topo da pilha 
        --topIndex;

        //se capacidade * 3/4 > topIndex, então reduzir o tamanho do array
        if(capacity * 3/4 > topIndex)
            reserve(capacity/2);

        //return verdadeiro
        return true;
    }


};

int main()
{
    DStack<int> myStack;
    int i;

    for(i=0;i<4;++i)
        myStack.push(i); // loop para  inserir elemetos no array(vetor)

    for(i=0;i<4;++i){
        cout<<myStack.top()<<' '; // (printf), retorna o elemento do topo da lista 
        myStack.pop(); // remove o elemento do topo da pilha 
    }
    cout<<endl;


    return 0;
}



