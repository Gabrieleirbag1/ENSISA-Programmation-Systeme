#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check(char *mot) {
    for (int i = 0; i < strlen(mot); i++)
    {
        if (mot[i] != '\0' && isalpha(mot[i])) // Check first character
        {
            continue;
        }
        return 0;
    }
    return 1;
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
        if (check(mot)) {
            printf("%s \n", mot);
        }
        mot = strtok(NULL, " - ");
    }

    return 0;
}