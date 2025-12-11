#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

ssize_t compteur;
volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void write_file(char *content)
{
    FILE *fp2;
    fp2 = fopen("tata", "a");
    if (fp2 != NULL)
    {
        for (int i = 0; i < strlen(content); i++)
        {
            putc(content[i], fp2);
        }
        fclose(fp2);
    }
}

void handle_sigint(int sig_num)
{
    sigint_flag = 1;
}

void handle_sigterm(int sig_num)
{
    sigterm_flag = 1;
}

int main()
{
    struct sigaction s;
    s.sa_handler = handle_sigint;
    sigaction(SIGINT, &s, NULL);

    struct sigaction s2;
    s.sa_handler = handle_sigterm;
    sigaction(SIGTERM, &s, NULL);

    while (1)
    {
        compteur++;

        if (sigint_flag == 1)
        {
            struct timeval t;

            if (gettimeofday(&t, NULL) == -1)
            {
                perror("gettimeofday failed");
                exit(EXIT_FAILURE);
            }
            double time_in_seconds = t.tv_sec + (t.tv_usec / 1000000.0);

            char str_compteur[20];
            char str_time[20];
            char content[40];

            sprintf(str_compteur, "%ld", compteur);
            sprintf(str_time, "%.6f", time_in_seconds);

            strcpy(content, str_compteur);
            strcat(content, " ");
            strcat(content, str_time);
            write_file(content);
            sigint_flag = 0;
        }

        if (sigterm_flag == 1)
        {
            char *content = "fin";
            write_file(content);
            exit(0);
        }

        if (compteur > 10000000000)
        {
            raise(SIGTERM);
        }
    }
    return 0;
}