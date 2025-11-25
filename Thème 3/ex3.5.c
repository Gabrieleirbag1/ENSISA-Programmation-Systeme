#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *buff = NULL;
    char *str = "tout le";

    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters = getline(&buff, &sizeAllocated, stdin);

    buff[strlen(buff) - 1] = '\0';

    for (unsigned int i = 0; i < strlen(buff); i++) {
        char content[strlen(str)];
        for (unsigned int j = 0; j < strlen(str); j++) {
            if (i + j < strlen(buff)) {
                content[j] = buff[i + j];
            } else {
                content[j] = '\0';
            }
        }

        int cmp = strncmp(content, str, strlen(str));

        if (cmp == 0) {
            printf("gg\n");
            break;
        }
    }
    free (buff);
    buff = NULL;
    
    return 0;
}