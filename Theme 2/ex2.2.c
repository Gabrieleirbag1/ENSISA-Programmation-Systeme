#include <stdio.h>
#include <string.h>

int main()
{   
    int c;
    int compteur = 1;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            compteur++;
        }
    }

    printf("Nombre de lignes : %d", compteur);

    return 0;
}