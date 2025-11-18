#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{   
    char c;
    char caracter = argv[1][0];
    int compteur = 0;

    while ((c = getchar()) != EOF) {
        if (c == caracter) {
            compteur++;
        }
    }

    printf("Nombre de '%c' : %d", caracter, compteur);

    return 0;
}