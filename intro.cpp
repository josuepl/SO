// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
int main() {
    // Write C++ code here
    int h0, h1;
    h0 = fork();
    if(h0 == 0){// HIJO 0
        cout << "HIJO: Hola mundo-> PID: ";
        cout << getpid()<< " PPID: ";
        cout << getppid()<<"\n";
    }
    else{//PADRE
        sleep(1);
        if((h1 = fork()) == 0){//HIJO 1
            cout << "H1: Hola mundo-> PID: ";
            cout << getpid()<< " PPID: ";
            cout << getppid()<<"\n";
            
        }
        else{
            sleep(1);
            cout << "PADR:Hola mundo->PID: ";
            cout << getpid()<< " PPID: ";
            cout << getppid()<<"\n";
        }
            
    }
