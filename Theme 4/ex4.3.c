#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct mot
{
    char *texte;         // texte associé au mot
    int nb_occurrences;  // nb d’occurrences du mot
    struct mot *suivant; // liste chaînée
};
struct mot *tete;

void initialiser_mots(void)
{
    char *str = "il fait beau, n'est-il pas ?";
    int j = 0;
    struct mot *current = tete;
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        char c = str[i];
        if (c == ' ')
        {
            j = 0;
            struct mot *new;
            current->suivant = new;
            current = new;
            continue;
        }
        else if (!isalnum(c))
        {
            continue;
        }
        current->texte[j] = c;
        j++;
    }
}

struct mot *trouver_mot(char text[])
{
}

void mettre_a_jour_mot(struct mot *mot)
{
}

void afficher_mots(void)
{
}

int main () {
    initialiser_mots();
    return 0;
}