#include <stdio.h>
#include <string.h>
#include <ctype.h>

void deleteNonAlphaChar(char *mot) {
    int writeIndex = 0;
    
    for (int i = 0; i < strlen(mot); i++)
    {
        if (isalpha(mot[i]))
        {
            mot[writeIndex] = mot[i];
            writeIndex++;
        }
    }
    mot[writeIndex] = '\0';  // End la string au nouvel index
}

int main()
{
    char phrase_str[1024] = "";
    int index = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF && index < 1023)
    {
        phrase_str[index++] = (char)c;
    }
    phrase_str[index] = '\0';

    char *mot = strtok(phrase_str, " - ");

    while (mot != NULL)
    {
        deleteNonAlphaChar(mot);
        printf("%s \n", mot);
        mot = strtok(NULL, " - ");
    }

    return 0;
}