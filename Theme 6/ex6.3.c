#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void create_processes(int n, int m, int c) {
    if (c >= m) {
        return;
    }
    for(int i=0;i<n;i++)
    {
        pid_t p = fork();
        if (p < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        
        if (p == 0) {
            printf("Fils %d créé (PID = %d)\n", i, getpid());
            if (c <= m) {
                c++;
                create_processes(n, m, c);}
                for (int j = 0; j < n && c + 1 < m; j++) {
                wait(NULL);
            }
            exit(i);
        }
    }
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int c = 0;

    create_processes(n, m, c);

    for(int i=0;i<n;i++) {
        int status;
        pid_t son_pid = wait(&status);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Code de retour du fils: %d\n", exit_code);
        }
    }
    
}


