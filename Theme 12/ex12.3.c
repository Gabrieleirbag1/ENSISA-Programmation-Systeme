#define MAX 10
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int last_thread_num;

void *compteur(void *arg) {
    int num = *(int *)arg;
    unsigned int count = 0;
    for (count = 0; count < 10; count++) {
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = (rand() % 1000000000);
        nanosleep(&ts, NULL);
        printf("Thread %d: compteur = %u\n", num, count + 1);
    }

    last_thread_num = num;

    return NULL;
}

int main() {
    pthread_t tid[MAX];
    int thread_nums[MAX];
    int i;
    
    for (i = 0; i < MAX; i++) {
        thread_nums[i] = i + 1;
        if (pthread_create(&tid[i], NULL, &compteur, &thread_nums[i]) == -1) {
            perror("pthread_create");
            return 1;
        }
    }
    
    for (i = 0; i < MAX; i++) {
        if (pthread_join(tid[i], NULL) == -1) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("\nDenier thread: %d \n", last_thread_num);
    
    return 0;
}