#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

class Array: private vector<int>{
    void sawp(unsigned i, unsigned j){
        unsigned aux;

        aux = at(i);
       vector<int>:: at(i) = at(j);
        vector<int> ::at(j) = aux;
    }
    public:
    
    int& operator[](unsigned n){
        return vector<int>:: at(n);
    }
     int size()const{
        return vector<int>:: size();
     }
     const  int at(size_type n )const{
        return vector<int>:: at(n);
     }

     void insert(unsigned n){
        
        push_back(n);

        for(int i= size()-1; i>0;--i){
            if(vector<int>::at(i)<vector<int>::at(i-1))
            sawp(i,i-1);
        }
     }

     void insertmid(unsigned n){
        push_back(n);

        for(int i= size()/2; i<size();++i){

           sawp(i,size()-1);
        }
     }

};

int main(){
    Array v;

    int i;

    v.insert(40);
    v.insert(30);
    v.insert(60);
    v.insert(50);
    v.insert(10);
    v. insertmid(35);
      v. insertmid(34);
    for(i=0; i<v.size();i++){
        cout<<v[i]<< " ";
    }

    return 0;
}