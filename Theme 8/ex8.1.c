#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void copier(int fdsrc, int fddst)
{
    char caracter;
    ssize_t n;
    while ((n = read(fdsrc, &caracter, 1)) > 0)
    {
        if (write(fddst, &caracter, n) != n)
        {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{
    copier(0, 1);

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
        close(fd[1]);
        copier(fd[0], 1);
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        copier(0, fd[1]);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}