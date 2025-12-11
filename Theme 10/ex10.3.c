#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANARY_SIZE 4
#define CANARY_VALUE 0xDEADBEEF

char *mon_malloc(size_t size)
{
    size_t total_size = CANARY_SIZE + size + CANARY_SIZE;
    char *p = (char *)malloc(total_size * sizeof(char));
    if (p == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    unsigned int canary = CANARY_VALUE;
    memcpy(p, &canary, CANARY_SIZE);
    memcpy(p + CANARY_SIZE + size, &canary, CANARY_SIZE);

    return p + CANARY_SIZE;
}

void mon_free(char *ptr, size_t size)
{
    if (ptr == NULL)
    {
        printf("Pointer is NULL\n");
        exit(EXIT_FAILURE);
    }

    char *p = ptr - CANARY_SIZE;

    size_t total_size = CANARY_SIZE + size + CANARY_SIZE;
    unsigned int canary_before, canary_after;
    memcpy(&canary_before, p, CANARY_SIZE);
    memcpy(&canary_after, p + CANARY_SIZE + size, CANARY_SIZE);

    if (canary_before != CANARY_VALUE || canary_after != CANARY_VALUE)
    {
        printf("Memory corruption detected: Canary value mismatch\n");
        exit(EXIT_FAILURE);
    }

    free(p);
}

int main()
{
    char *ptr = mon_malloc(10);
    printf("Allocated memory at address: %p\n", (void *)ptr);
    mon_free(ptr, 10);

    char *ptr2 = mon_malloc(11);
    printf("Allocated memory at address: %p\n", (void *)ptr2);
    mon_free(ptr2, 10);
    return 0;
}