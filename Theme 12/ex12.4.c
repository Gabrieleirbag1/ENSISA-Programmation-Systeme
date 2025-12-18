#define MAX 4
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long int count;
pthread_mutex_t m;

void *compteur(void *arg)
{
    for (unsigned long int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&m);
        count++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main()
{
    pthread_t tid[MAX];
    int thread_nums[MAX];
    int i;

    pthread_mutex_init(&m, NULL);

    for (i = 0; i < MAX; i++)
    {
        thread_nums[i] = i + 1;
        if (pthread_create(&tid[i], NULL, &compteur, &thread_nums[i]) == -1)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for (i = 0; i < MAX; i++)
    {
        if (pthread_join(tid[i], NULL) == -1)
        {
            perror("pthread_join");
            return 1;
        }
    }
    printf("Compteur : %ld", count);
    return 0;
}

// problème constaté: la valeur du compteur est au delà de 1M (Compteur final: 1309868)