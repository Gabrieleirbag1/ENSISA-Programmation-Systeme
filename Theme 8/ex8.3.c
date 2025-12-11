#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t p = fork();

    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (p == 0)
    {
        while (1){}
    }
    else
    {
        close(fd[0]);
    }

    return 0;
}