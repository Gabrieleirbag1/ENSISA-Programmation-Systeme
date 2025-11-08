#include <stdio.h>
#include <string.h>

int main()
{   
    char test[] = "salut moi c est gabibou :)";
    char phrase_str[] = ""; 

    int c;
    while ((c = getchar()) != EOF) {
        strncat(phrase_str, &c, 1);
    }

    char* mot = strtok(phrase_str, " - ");

    int compteur = 0;

    while (mot != NULL) {
        mot = strtok(NULL, " - ");
        compteur++;
    }

    printf("Il y a %d mot(s) :) dans la phrase.\n", compteur);

    return 0;
}