#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *nom;
    if (!argv[1])
    {
        nom = getenv("USER");
    }
    else
    {
        nom = argv[1];
    }

    int n_process = 2;

    int pipes[n_process][2];
    for (int i = 0; i < n_process; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe failed");
            return 1;
        }
    }

    for (int i = 0; i < n_process; i++)
    {
        pid_t p = fork();

        if (p < 0)
        {
            perror("fork failed");
            return 1;
        }

        if (p == 0)
        {
            if (i == 0)
            {
                dup2(pipes[0][0], 0);
                dup2(pipes[1][1], 1);
                for (int j = 0; j < n_process; j++)
                {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
                char pattern[256];
                snprintf(pattern, sizeof(pattern), "^%s", nom);
                execlp("grep", "grep", pattern, NULL);
                perror("execlp failed");
                return 1;
            }
            else
            {
                dup2(pipes[1][0], 0);
                for (int j = 0; j < n_process; j++)
                {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
                execlp("wc", "wc", "-l", NULL);
                perror("execlp failed");
                return 1;
            }
        }
    }

    dup2(pipes[0][1], 1);
    for (int j = 0; j < n_process; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
    execlp("ps", "ps", "eaux", NULL);
    perror("execlp failed");
    return 1;
}