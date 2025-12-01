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
}

void ajouter_element(int clef, char *valeur) {
    struct element *new_tete = malloc(sizeof(struct element));
    new_tete->clef = clef;
    new_tete->valeur = &valeur;
    new_tete->suivant = &tete;
    new_tete->precedent = tete.precedent;
    tete.precedent->suivant = new_tete;
    tete.precedent = new_tete;
}

char *lire_valeur(int clef) {
    if (tete.clef == clef) {
        return tete.valeur;
    } else {
        lire_valeur(tete.suivant->clef);
    }
}

void retirer_element(int clef) {
    if (tete.clef == clef) {
        tete.clef = 0;
        tete.precedent->suivant = tete.suivant;
        tete.suivant->precedent = tete.precedent;
        free(tete);
    } else {
        retirer_element(tete.suivant->clef);
    }
}