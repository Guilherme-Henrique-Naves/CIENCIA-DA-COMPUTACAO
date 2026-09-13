#include <iostream>
#include <vector>

using namespace std;

template <class T>
class DOrderedArrayFromVector : private vector<int>{

    // SWAP-> verifica o elemento e inverte os valores
    void swapIndex(unsigned i,unsigned j){
        T aux;

        aux = at(i);
        vector<int>::at(i) = at(j);
        vector<int>::at(j) = aux;
    }
    //void push_back (const int &val){}
public:


    // Insere um elemento do array 
    void orderedInsert(T n){
        unsigned i;

        vector<int>::push_back(n); // Insere o elemento no final do array
        
        for(i = size()-1;i>0;--i) // loop para percorrer todo o array de tras para frente
            if(vector<int>::at(i)<vector<int>::at(i-1)) // verifica se existe um elemento fora de ordem e inverte as posições
                
                swapIndex(i,i-1); // função para inverter dois elementos

    }
    // size -> Tamanho do array
    int size() const{
        return vector<int>::size();
    }
    T at (size_type n){
        return vector<int>::at(n);
    }
    const T at (size_type n) const{
        return vector<int>::at(n);
    }
};
int main()
{
    DOrderedArrayFromVector<int> V;
    int i;

    V.orderedInsert(50);
    V.orderedInsert(10);
    V.orderedInsert(30);
    V.orderedInsert(40);
    V.orderedInsert(60);
    V.orderedInsert(100);

    //V.push_back(0);
    for(i=0;i<V.size();++i)
        cout<<V.at(i)<<' ';
    cout<<endl;

    return 0;
}










