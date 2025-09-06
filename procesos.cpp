#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

int main(){
    char buffer[10];
    int x = 5, fd[2],f2d[2];
    pid_t a, b;
    pipe(fd);
    pipe(f2d);
    if((a = fork()) == 0){
        x = 10;
        buffer[0] = 'H';
        buffer[1] = 'O';
        buffer[2] = 'L';
        buffer[3] = 'A';
        cout<<"A: "<<x<<" "<<buffer<<endl;
        write(fd[1], buffer,4);
        write(f2d[1],&x,sizeof(int));
    }else//padre
    {
        waitpid(a, NULL, 0);
        read(fd[0], buffer, 4);
        read(f2d[0],&x, sizeof(int));
        if((b = fork()) == 0){
            buffer[4] ='-';
            buffer[5] ='M';
            buffer[6] ='U';
            buffer[7] ='N';
            buffer[8] ='D';
            buffer[9] ='O';
            cout<<"B: "<<x<<" "<<buffer<<endl;
            write(fd[1],buffer, 10);
        }else{//padre
            waitpid(b,NULL,0);
            read(fd[0],buffer,10);
            cout<<"P: "<<x<<": "<<buffer<<endl;
        }   
    }    
    return 0;
}