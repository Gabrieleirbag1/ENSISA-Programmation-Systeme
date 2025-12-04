#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element
{
    int clef;                  // clef de recherche
    char *valeur;              // valeur associée
    struct element *suivant;   // suivant dans la liste
    struct element *precedent; // précédent dans la liste
} elem; 
struct element tete;

void initialiser_liste(void) {
    tete.suivant = &tete;
    tete.precedent = &tete;
    tete.clef = -1;
    tete.valeur = NULL;
}

void ajouter_element(int clef, char *valeur) {
    struct element *new_tete = malloc(sizeof(struct element));
    new_tete->clef = clef;
    new_tete->valeur = valeur;
    new_tete->suivant = &tete;
    new_tete->precedent = tete.precedent;
    tete.precedent->suivant = new_tete;
    tete.precedent = new_tete;
}

char *lire_valeur(int clef) {
    struct element *currentTete = tete.suivant;
    if (currentTete == &tete) {
        return "Not found";
    }
    if (currentTete->clef == clef) {
        return currentTete->valeur;
    } else {
        tete.suivant = currentTete->suivant;
        char *resultat = lire_valeur(clef);
        tete.suivant = currentTete;
        return resultat;
    }
}

void retirer_element(int clef) {
    struct element *currentTete = tete.suivant;
    if (currentTete == &tete) {
        return;
    }
    if (currentTete->clef == clef) {
        currentTete->precedent->suivant = currentTete->suivant;
        currentTete->suivant->precedent = currentTete->precedent;
        free(currentTete);
    } else {
        tete.suivant = currentTete->suivant;
        retirer_element(clef);
        tete.suivant = currentTete;
    }
}

int main() {
    initialiser_liste();
    ajouter_element(1, "Bonjour");
    ajouter_element(2, "Salut");
    printf("%s\n", lire_valeur(1));
    printf("%s\n", lire_valeur(2));
    retirer_element(1);
    printf("%s\n", lire_valeur(1));
    printf("%s\n", lire_valeur(2));
    return 0;
}