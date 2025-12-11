#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handle_signal(int signal_num)
{
    printf("Received signal: %d\n", signal_num);
}

int main()
{
    signal(SIGINT, handle_signal);

    pid_t pid = getpid();

    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            printf("Sending SIGINT to process %d\n", pid);
            kill(pid, SIGINT);
        } else {
            raise(SIGINT);
        }
    }
    return 0;
}