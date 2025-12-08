#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(1);
    }
    printf("parentpid = %d, pid = %d \n",getppid(), getpid());

    if (p == 0) {
        int pid = getpid();
        int last_digit_pid = pid % 10;
        exit(last_digit_pid);
    } else {
        int son_pid = p;
        int status;
        printf("son pid = %d\n", son_pid);
        wait(&status);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Code de retour du fils: %d\n", exit_code);
        }
    }

    return 0;
}