#include <iostream>
#include <thread>

using namespace std;

void calcula(int base){
    cout<<"Tabla del numero: "<<base<<endl;
    for(int i = 1; i<=10;i++){
        cout<<base <<" X "<<i <<" = "<<base*i<<endl;
    }
}

int main(){
    thread b2(calcula,2);
    thread b4(calcula,4);
    thread b6(calcula,6);
    if(b2.joinable()){
        b2.join();
    }
    if(b4.joinable()){
        b4.join();
    }
    if(b6.joinable()){
        b6.join();
    }
    
}