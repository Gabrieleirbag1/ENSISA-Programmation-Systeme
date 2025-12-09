#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int lower_bound = 1;

    int rand_values[n];

    for (int i = 0; i < n; i++)
    {
        int value = rand() % (m - lower_bound + 1) + lower_bound;
        rand_values[i] = value;
    }

    for (int i = 0; i < n; i++)
    {
        pid_t p = fork();
        if (p < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (p == 0)
        {
            sleep(rand_values[i]);
            exit(rand_values[i]);
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
        }
    }

    return 0;
}