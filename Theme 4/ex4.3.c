#include <stdio.h>
#include <stdlib.h>
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
    tete = NULL;
    struct mot *current = NULL;
    char buffer[100];
    int j = 0;
    
    for (unsigned int i = 0; i <= strlen(str); i++)
    {
        char c = str[i];
        if (c == ' ' || c == '\0' || !isalnum(c))
        {
            if (j > 0) {  // si on a un mot à ajouter
                buffer[j] = '\0';  // terminer la chaîne
                
                struct mot *new = malloc(sizeof(struct mot));
                new->texte = strdup(buffer);  // copier le mot
                new->nb_occurrences = 1;
                new->suivant = NULL;
                
                if (tete == NULL) {
                    tete = new;
                    current = tete;
                } else {
                    current->suivant = new;
                    current = new;
                }
                j = 0;
            }
        }
        else if (isalnum(c))
        {
            buffer[j] = c;
            j++;
        }
    }
}

struct mot *trouver_mot(char text[])
{
    struct mot *before = NULL;
    struct mot *next = tete;
    while (next != NULL) {
        if (strcmp(next->texte, text) == 0) {
            return next;
        }
        before = next;
        next = next->suivant;
    }
    next = malloc(sizeof(struct mot));
    before->suivant = next;
    next->texte = text;
    return next;
}


void mettre_a_jour_mot(struct mot *mot)
{
    struct mot *before = NULL;
    struct mot *next = tete;
    mot->nb_occurrences = 0;
    while (next != NULL) {
        if (strcmp(next->texte, mot->texte) == 0) {
            mot->nb_occurrences += 1;
            next->nb_occurrences = mot->nb_occurrences;
        }
        before = next;
        next = next->suivant;
    }
}

void afficher_mots(void)
{
    struct mot *current = tete;
    while (current != NULL) {
        printf("Mot: %s, Occurrences: %d\n", current->texte, current->nb_occurrences);
        current = current->suivant;
    }
}

int main () {
    initialiser_mots();
    struct mot *motBeau = trouver_mot("il");
    printf("Mot trouvé: %s\n", motBeau->texte);
    mettre_a_jour_mot(motBeau);
    printf("Nombre d'occurrences de '%s': %d\n", motBeau->texte, motBeau->nb_occurrences);
    afficher_mots();
    return 0;
}