#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
    int n;
    int p;
    int t;
    long ut;
};

void *fonction(void *arg) {
    struct arguments *args = (struct arguments *)arg;
    long sum = 0;
    
    // Calculer ((t-1)*p + i)
    for (int i = 1; i <= args->p; i++) {
        sum += (args->t - 1) * args->p + i;
    }
    
    args->ut = sum;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if (argc < 3){
        printf("Usage: ./ex12.2 n p\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int p = atoi(argv[2]);

    struct arguments args[n];

    for (int t = 1; t <= n; t++) {
        args[t-1].n = n;
        args[t-1].p = p;
        args[t-1].t = t;
        args[t-1].ut = 0;
    }

    pthread_t tid[n];
    int i; 
    for (i = 0; i < n; i++)
        if (pthread_create(&tid[i], NULL, fonction, (void *)&args[i]) == -1) {
            perror("pthread_create");
            exit(1);
        }
    for (i = 0; i < n; i++)
        if (pthread_join(tid[i], NULL) == -1) {
            perror("pthread_join");
            exit(1);
        }

    long total = 0;
    for (int t = 0; t < n; t++) {
        total += args[t].ut;
    }
    printf("Sum of all ut values: %ld\n", total);

    return 0;
}