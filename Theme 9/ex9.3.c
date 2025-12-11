#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


void handle_signal(int signal_num)
{
    printf("Received signal: %d\n", signal_num);
    psignal(signal_num, "Signal description");
}

int main()
{
    signal(SIGILL, handle_signal);

    pid_t pid = getpid();

    raise(SIGILL);

    return 0;
}