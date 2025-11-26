#include <stdio.h>
#include <stdlib.h>

int lire_tableau(int *tableau, int max_elem, int *nb_elem)
{
    char *buff = NULL;
    *nb_elem = 0;
    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters;
    while ((characters = getline(&buff, &sizeAllocated, stdin)) != EOF)
    {
        int number = atoi(buff);
        *(tableau + *nb_elem) = number;
        (*nb_elem)++;
        printf("Converted %i\n", number);
        if (*nb_elem >= max_elem) {
            return -1;
        }
    }
    return 0;
}

void trier_tableau(int *tableau, int nb_elem) {
    for (unsigned int i = 0; i < nb_elem - 1; i++)
    {
        for (unsigned int j = i + 1; j < nb_elem; j++)
        {
            if (*(tableau + i) > *(tableau + j))
            {
                int temp = *(tableau + i);
                *(tableau + i) = *(tableau + j);
                *(tableau + j) = temp;
            }
        }
    }
}


void afficher_tableau(int *tableau, int nb_elem) {
    for (unsigned int i = 0; i < nb_elem; i++) {
        printf("%i|", *(tableau + i));
    }
}

int main()
{   
    int max_elem = 100;
    int tableau[max_elem];
    int nb_elem = 0;
    lire_tableau(tableau, max_elem, &nb_elem);
    trier_tableau(tableau, nb_elem);
    afficher_tableau(tableau, nb_elem);
    return 0;
}