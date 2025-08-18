#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
int main(){
    int fd[2], ph;
    char buffer[10];
    cout<< " BUFFER: "<<buffer<<endl;
    pipe(fd);
    if((ph = fork()) == 0){//HIJO
        cout<< " HBUFFER: "<<buffer<<endl;
        buffer[0]='H';
        buffer[1]='O';
        buffer[2]='L';
        buffer[3]='A';
        write(fd[1],&buffer,4);
        sleep(1);
        read(fd[0],buffer,10);
        cout<< " HBUFFER: "<<buffer<<endl;
    }else{//PADRE
        sleep(1);
        read(fd[0],buffer,4);
        buffer[4] = '_';
        buffer[5] = 'M';
        buffer[6] = 'U';
        buffer[7] = 'N';
        buffer[8] = 'D';
        buffer[9] = 'O';
        write(fd[1], &buffer,10);
        sleep(1);
        cout<< " PBUFFER: "<<buffer<<endl;
    }   
    return 0;
}