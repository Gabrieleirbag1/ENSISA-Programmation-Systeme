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

    int strindex = 0;
    int isValid = 0;
    int compteur = 0;
    for (int i=0; i<strlen(buff); i++) {
        char buffValue = buff[i];
        char strValue = str[strindex];
        if (compteur == strlen(str)) {
            puts("gg");
            break;
        }
        if (buffValue == strValue && strindex < strlen(str)) {
            isValid = 1;
            strindex++;
            compteur++;
        } else {
            if (isValid) {
                strindex = 0;
                compteur = 0;
            }
        }
    }

    free (buff);
    buff = NULL;
    
    return 0;
}