#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    pid_t h1, h2;
    int x;
    if((h1=fork()) == 0){//H1
        cout<< "H1 "<<"PID: "<<getpid()<<" PPID: "<<getppid()<<"\n";
        cout<<"Ingresa un numero\n";
        cin>>x;
    }else{//PADRE
        waitpid(h1, NULL, 0);
        if((h2=fork())== 0){//h2
            cout<< "H2 "<<"PID: "<<getpid()<<" PPID: "<<getppid()<<"\n";
            cout<<"Ingresa un numero\n";
            cin>>x;
        }else{//PADRE
            waitpid(h2, NULL,0);
            cout<< "PADRE "<<"PID: "<<getpid()<<" PPID: "<<getppid()<<"\n";
        } 
    }

    return 0;
}