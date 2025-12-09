#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    char *cmd = argv[2];

    char **args = malloc((argc - 1) * sizeof(char *));
    if (!args)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    args[0] = cmd;
    for (int i = 3; i < argc; i++)
    {
        args[i - 2] = argv[i];
    }
    args[argc - 2] = NULL;

    pid_t p = fork();
    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        if (p == 0)
        {
            execvp(cmd, args);
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < n; i++)
    {
        int status;
        pid_t son_pid = wait(&status);
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("Code de retour du fils: %d\n", exit_code);
            if (exit_code != 0) {
                free(args);
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
