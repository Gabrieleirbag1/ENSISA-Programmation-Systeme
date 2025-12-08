#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/times.h>

int main(int argc, char *argv[])
{
    pid_t p = fork();
    char *dir = argv[1];

    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (p == 0)
    {
        close(1); 
        if (open("/dev/null", O_WRONLY) == -1) {
            perror("open /dev/null failed");
            exit(EXIT_FAILURE);
        }
        execlp("ls", "ls", "-R", dir, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        struct tms t;
        if (times(&t) == -1) {
            perror("times failed");
            exit(EXIT_FAILURE);
        }

        printf("Temps %f seconds", (double)(t.tms_cutime + t.tms_cstime ) / 100);

    }

    return 0;
}