#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
int main() {
    // Write C++ code here
    
    int ph, ph2;
    fork();
    if( (ph = fork()) == 0){//HIJO
    cout<<"HIJO 1 pid: "<<getpid()<<" ppid: "<<getppid()<<"\n"; 
    }else{//PADRE
    cout << "PADRE pid: "<<getpid()<<" ppid: "<<getppid()<<"\n";
    cout <<"Cree un hijo con pid: "<<ph<<"\n";
        if((ph2 = fork()) == 0){//HIJO 2
            cout<<"HIJO 2 pid: "<<getpid()<<" ppid: "<<getppid()<<"\n"; 
        }else{//PADRE
            cout<<"PADRE pid: "<<getpid()<<" ppid: "<<getppid()<<"\n"; 
        }
    }


    return 0;
}