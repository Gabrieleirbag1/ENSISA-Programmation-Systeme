#include <stdio.h>
#include <stdlib.h>

void afficher_tableau(double *tableau, int nb_elem)
{
    for (unsigned int i = 0; i < nb_elem; i++)
    {
        printf("%f|", tableau[i]);
    }
}

void trier_tableau(double *tableau, int nb_elem) {
    for (unsigned int i = 0; i < nb_elem - 1; i++)
    {
        for (unsigned int j = i + 1; j < nb_elem; j++)
        {
            if (tableau[i] > tableau[j])
            {
                int temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }
}

int lire_tableau(double **tableau, int *nb_elem)
{
    char *buff = NULL;
    *nb_elem = 0;
    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters;

    int n = 2;
    *tableau = calloc(n, sizeof(double));

    while ((characters = getline(&buff, &sizeAllocated, stdin)) != EOF)
    {
        double number = atof(buff);
        (*tableau)[*nb_elem] = number;
        (*nb_elem)++;
        printf("Converted %f\n", number);
        if (*nb_elem == n)
        {
            printf("NOUVELLE TAILLE\n");
            trier_tableau(*tableau, *nb_elem);
            afficher_tableau(*tableau, *nb_elem);

            double *old_tableau = *tableau;
            int old_n = n;
            n = n * 2;
            *tableau = calloc(n, sizeof(double));

            for (unsigned int j = 0; j < old_n; j++)
            {
                (*tableau)[j] = old_tableau[j];
            }

            free(old_tableau);
            continue;
        }
    }
    return 0;
}

int main()
{
    double *tableau = NULL;
    int nb_elem = 0;
    lire_tableau(&tableau, &nb_elem);
    return 0;
}