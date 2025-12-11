#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

bool print_flag = false;

void handle_alarm(int sig)
{
    print_flag = true;
}

int main()
{

    pid_t p = fork();

    if (p < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (p == 0)
    {
        signal(SIGALRM, handle_alarm);
        alarm(1);
        for (;;)
        {
            sleep(5);
            if (print_flag)
            {
                printf("Hello\n");
                print_flag = false;
                alarm(1);
            }
        }
    }
    else
    {
        sleep(60);
        kill(p, SIGUSR1);
    }
}
