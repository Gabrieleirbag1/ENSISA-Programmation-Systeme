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

    int n_process = 3;
    int n_pipes = n_process - 1;

    int pipes[n_process][2];

    for (unsigned int i = 0; i < n_pipes; i++)
    {
        pid_t p = fork();

        if (p < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (p == 0)
        {
            close(pipes[i][1]);
            for (int j = 0; j < n_pipes; j++)
            {
                if (j != i && j != i + 1)
                {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }
            close(pipes[i][1]);
            copier(pipes[i][0], pipes[i][1]);
            close(pipes[i][0]);
        }
        else
        {
            close(pipes[0][0]);
            for (int i = 1; i < n_pipes; i++)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            close(pipes[n_pipes - 1][1]);

            copier(0, pipes[0][1]);
            close(pipes[0][1]);

            copier(pipes[n_pipes - 1][0], 1);
            close(pipes[n_pipes - 1][0]);

            for (int i = 0; i < n_pipes; i++)
            {
                wait(NULL);
            }
        }
    }

    return 0;
}