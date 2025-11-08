#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *buff = NULL;
    char buff2[1024];

    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters = getline(&buff, &sizeAllocated, stdin);

    strcpy(buff2, buff);

    puts(buff2);
    printf("Longueur: %ld \n", strlen(buff2) - 1);
    
    free (buff);
    buff = NULL;
    
    return 0;
}