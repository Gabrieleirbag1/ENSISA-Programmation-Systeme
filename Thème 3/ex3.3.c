#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char strings[][100], int *index)
{
    for (unsigned int i = 0; i < *index - 1; i++)
    {
        for (unsigned int j = i + 1; j < *index; j++)
        {
            if (strcmp(strings[i], strings[j]) > 0)
            {
                char temp[100];
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }
    }
}

int main()
{
    char strings[1000][100];
    char *buff = NULL;
    int index = 0;

    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters;

    while ((characters = getline(&buff, &sizeAllocated, stdin)) != EOF)
    {
        buff[strcspn(buff, "\n")] = '\0';
        
        strcpy(strings[index++], buff);

        sort(strings, &index);

        printf("Ajouté: %s\n", buff);
    }

    printf("\nListe triée:\n");
    for (int i = 0; i < index; i++)
    {
        printf("%s\n", strings[i]);
    }

    free(buff);
    buff = NULL;

    return 0;
}