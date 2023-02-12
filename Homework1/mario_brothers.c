#include <string.h>
#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h>

const int MAX = 101;

int main(){


    int p1[2];
    int p2[2];

    pid_t pid;

    if (pipe(p1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    if (pipe(p2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 2;
    }

    pid = fork();

    if (pid < 0) {
    fprintf(stderr, "fork Failed");
    return 1;
    }

    else if (pid > 0){
        char string[MAX];
        char string_flipped[MAX];

        printf("Please input a string: ");
        scanf("%[^\n]%*c", string);

        strncpy(string, string, MAX-1);

        close(p1[0]);
        close(p2[1]);

        write(p1[1], string, MAX-1);

        wait(NULL);

        int num_read = read(p2[0], string_flipped, MAX);

        printf("Flipped String: %s\n", string_flipped);

        close(p1[1]);
        close(p2[0]);

    }
    else{
        close(p1[1]);
        close(p2[0]);
        char string_flipped[MAX];
        
        int num_read = read(p1[0], string_flipped, MAX);

        for (int i = 0; string_flipped[i]!='\0'; i++)
  	    {
  		    if(string_flipped[i] >= 65 && string_flipped[i] <= 90)
  		    {
  		    	string_flipped[i] += 32;
		    }
		    else if(string_flipped[i] >= 97 && string_flipped[i] <= 122)
  		    {
  			    string_flipped[i] -= 32;
		    }
  	    }

        close(p1[0]);
        close(p2[0]);

        write(p2[1], string_flipped, num_read);
    }

    return 0;
}