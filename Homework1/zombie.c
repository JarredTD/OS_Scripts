#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h> 


int main(){
    pid_t pid;

    pid = fork();

    while (1){
        if (pid == 0){
            return 0;
        }

        else {
            sleep(30);
            return 0;
        }
    }

}