#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char buffer[1024];
    int fp = open(argv[1], O_RDONLY);

    pid_t p = fork();
    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    char c;
    int count = 0;
    ssize_t bytes_read;

    while ((bytes_read = read(fp, &c, 1)) > 0)
    {
        printf("%c", c);
        count++;
    }

    printf("\n[%s - PID %d] Nombre de caractères lus: %d\n",
           (p == 0) ? "FILS" : "PERE", getpid(), count);

    close(fp);
    printf("%s", buffer);
    return 0;
}