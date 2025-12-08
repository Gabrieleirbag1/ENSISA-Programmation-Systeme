#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int n = 5;
    for(int i=0;i<n;i++)
    {
        pid_t p = fork();
        if (p < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        
        if (p == 0) {
            printf("Fils %d créé (PID = %d)\n", i, getpid());
            exit(i);
        }
    }
    for(int i=0;i<n;i++) {
        int status;
        pid_t son_pid = wait(&status);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Code de retour du fils: %d\n", exit_code);
        }
    }
    
}


