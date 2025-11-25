#include <stdio.h>
#include <stdlib.h>

int lire_tableau(double *tableau, int max_elem, int *nb_elem)
{
    int numbers[1000];
    char *buff = NULL;
    int index = 0;

    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters;
    while ((characters = getline(&buff, &sizeAllocated, stdin)) != EOF)
    {
        double number = atof(buff);
        numbers[index++] = number;
        printf("Converted %f\n", number);
    }
}

void trier_tableau(double *tableau, int nb_elem) {}

void afficher_tableau(double *tableau, int nb_elem) {}

int main()
{   
    int max_elem = 100;
    double *tableau[max_elem];
    int *nb_elem = 0;
    lire_tableau(*tableau, max_elem, nb_elem);
    return 0;
}