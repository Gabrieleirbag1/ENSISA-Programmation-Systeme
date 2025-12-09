#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void copier(int fdsrc, int fddst)
{
    char buf[1024];  // Tampon de 1024 octets pour lire/écrire par blocs
    ssize_t n;
    while ((n = read(fdsrc, buf, sizeof(buf))) > 0) {
        if (write(fddst, buf, n) != n) {
            perror("write failed");
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    // Test de la fonction copier (étape 1) : recopier stdin vers stdout
    copier(0, 1);

    // Le reste du programme (pipe, fork, etc.) sera ajouté à l'étape 2
    // Pour l'instant, commentez ou supprimez les lignes suivantes pour tester seulement copier
    /*
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t p = fork();

    if (p < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (p == 0)
    {
    }
    else
    {
        wait(NULL);
    }
    */
    return 0;
}