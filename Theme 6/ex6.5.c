#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    struct timeval start, end;
    char *dir = argv[1];

    if (gettimeofday(&start, NULL) == -1)
    {
        perror("gettimeofday failed");
        exit(EXIT_FAILURE);
    }
    double time_in_seconds = start.tv_sec + (start.tv_usec / 1000000.0);
    printf("Heure de départ : %.6f secondes au départ\n", time_in_seconds);

    pid_t p = fork();
    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (p == 0)
    {
        execlp("ls", "ls", "-l", dir, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        if (gettimeofday(&end, NULL) == -1)
        {
            perror("gettimeofday failed");
            exit(EXIT_FAILURE);
        }

        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        double final_time = end.tv_sec + (end.tv_usec / 1000000.0);
        printf("Heure finale : %.6f secondes depuis l'époque\n", final_time);
        printf("Temps écoulé pendant l'appel à ls : %.6f secondes\n", elapsed);
    }

    return 0;
}