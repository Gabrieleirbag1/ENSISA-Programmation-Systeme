#define MAX 10
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fonction(void *arg)
{
    printf("%d\n", *(int *)arg); // Imprime la valeur
    return NULL;
}
void erreur(char *msg)
{
    perror(msg); // fonction appelée en cas d'erreur de primitive (thread en l'occurrence)
    exit(1);
}
int main(int argc, char *argv[])
{
    pthread_t tid[MAX]; // tableau des identifiants des threads
    int i; 
    for (i = 0; i < MAX; i++) // création des threads
        if (pthread_create(&tid[i], NULL, &fonction, (void *)&i) == -1)
            erreur("pthread_create");
    for (i = 0; i < MAX; i++) // attente de la fin des threads
        if (pthread_join(tid[i], NULL) == -1)
            erreur("pthread_join");
}

// concrètement, ce script crée 10 threads qui impriment la valeur de i, et attend la fin de chacun des threads avant de terminer le programme principal.
// le problème c'est que comme i est partagé entre tous les threads et qu'il est modifié dans la boucle de création des threads, les threads peuvent imprimer des valeurs incohérentes (pas dans l'ordre). 
// il faudrait donc passer une copie distincte de i à chaque thread, on pourrait par exemplet utiliser un tableau pour stocker les valeurs.