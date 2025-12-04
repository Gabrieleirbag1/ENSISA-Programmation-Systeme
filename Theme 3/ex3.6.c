#include <stdio.h>

char *mon_strchr(char *chaine, int car)
{
    unsigned int index = 0;
    while (chaine[index] != '\0')
    {
        if (chaine[index] == car)
        {
            return &chaine[index];
        }
        index++;
    }
    return NULL;
}
int main()
{
    char *chaine = "Salut tout le monde";
    char car = 'o';

    char *result = mon_strchr(chaine, car);

    if (result != NULL)
    {
        printf("Character '%c' found at position: %ld\n",
               car, result - chaine);
    }
    else
    {
        printf("Character '%c' not found.\n", car);
    }
    return 0;
}