#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
 
const int NUM_ARR_SIZE = 100;
 
int main(int argc, char **argv) 
{ 
    if (argc == 1){
        fprintf(stderr, "No input given.\n");
        return 2;
    }

    char *end_ptr;
    int num = strtol(argv[argc-1], &end_ptr, 10);
    if (num <= 0){
        fprintf(stderr, "Positive integer inputs only.\n");
        return 3;
    }

    pid_t pid; 
    pid = fork(); 

    if (pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    else if (pid == 0) { /* child process */ 
        while (num != 1){
            printf("%i, ", num);

            if (num % 2 == 0){
                num = num / 2;
            } 
            else{
                num = 3 * num + 1;
            }
        }
        printf("1\n");
    } 

    else if (pid > 0) { /* parent process */ 
        wait(NULL); 

        printf("Complete");
        return 0; 
    } 
}