#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOM 50
#define MAXTEL 10
struct fiche
{
    int occupe;
    char nom[MAXNOM];
    char telephone[MAXTEL];
};
typedef struct fiche fiche;

struct fiche fiches[1000] = {{1, "Ram", "06010203"},
                         {1, "Mohan", "06050607"},
                         {1, "Ria", "06091011"}};

void chercher(char *nom)
{
    int numberFiches = sizeof(fiches) / sizeof(fiches[0]);
    for (unsigned int i = 0; i < numberFiches; i++)
    {
        if (strcmp(nom, fiches[i].nom) == 0)
        {
            printf("Trouvé: %s - Téléphone: %s\n", fiches[i].nom, fiches[i].telephone);
            return;
        }
    }
    printf("Personne non trouvée: %s\n", nom);
}

void afficher(char *tel)
{
    int numberFiches = sizeof(fiches) / sizeof(fiches[0]);
    for (unsigned int i = 0; i < numberFiches; i++)
    {
        if (strcmp(tel, fiches[i].telephone) == 0)
        {
            printf("Trouvé: %s - Nom: %s - Occupé: %d\n", fiches[i].telephone, fiches[i].nom, fiches[i].occupe);
            return;
        }
    }
    printf("Numéro non trouvé: %s\n", tel);
}

void ajouter(char *tel, char *nom){
    int numberFiches = sizeof(fiches) / sizeof(fiches[0]);
    for (unsigned int i = 0; i < numberFiches; i++)
    {
        if (fiches[i].occupe == 0)
        {
            strcpy(fiches[i].nom, nom);
            strcpy(fiches[i].telephone, tel);
            fiches[i].occupe = 1;
            printf("Ajouté: %s - Nom: %s - Occupé: %d\n", fiches[i].telephone, fiches[i].nom, fiches[i].occupe);
            return;
        }
    }
    strcpy(fiches[numberFiches+1].nom, nom);
    strcpy(fiches[numberFiches+1].telephone, tel);
    fiches[numberFiches+1].occupe = 1;
    printf("Ajouté: %s - Nom: %s - Occupé: %d\n", fiches[numberFiches+1].telephone, fiches[numberFiches+1].nom, fiches[numberFiches+1].occupe);
}

void detruire(char *tel){
    int numberFiches = sizeof(fiches) / sizeof(fiches[0]);
    for (unsigned int i = 0; i < numberFiches; i++)
    {
        if (strcmp(tel, fiches[i].telephone) == 0)
        {
            fiches[i].occupe = 0;
            printf("Supprimé: %s - Nom: %s - Occupé: %d\n", fiches[i].telephone, fiches[i].nom, fiches[i].occupe);
            return;
        }
    }
}

int main()
{
    char testNom[MAXNOM] = "Ram";
    char testNom2[MAXNOM] = "Samed";
    char testNom3[MAXNOM] = "Philou";
    char testTel[MAXTEL] = "06091011";
    char testTel2[MAXTEL] = "07891099";
    char testTel3[MAXTEL] = "O8919191";
    char testTel4[MAXTEL] = "09653721";

    chercher(testNom);
    afficher(testTel);
    afficher(testTel2);
    ajouter(testTel3, testNom2);
    detruire(testTel);
    ajouter(testTel4, testNom3);
    afficher(testTel3);
    afficher(testTel4);
    return 0;
}