#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int lire_16(void)
{
    char *buff = NULL;
    size_t sizeAllocated = 0;
    
    printf("> ");
    size_t characters = getline(&buff, &sizeAllocated, stdin);

    if (buff[characters - 1] == '\n') {
        buff[characters - 1] = '\0';
    }

    unsigned int result = 0;
    
    for (int i = 0; i < strlen(buff); i++)
    {
        result <<= 4;
        
        if (buff[i] >= 'A' && buff[i] <= 'F') {
            result += buff[i] - 'A' + 10;
        } else {
            result += buff[i] - '0';
        }
    }

    printf("Valeur hexadécimale: %s\n", buff);
    printf("Valeur décimale: %u\n", result);
    
    free(buff);
    return result;
}

int main()
{
    lire_16();
    return 0;
}