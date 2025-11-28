#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum code
{
    noeud,
    feuille
};
struct noeud
{
    enum code code;
    union
    {
        int valeur;
        struct
        {
            char operation;
            struct noeud *fils_gauche;
            struct noeud *fils_droit;
        } s;
    } u;
};

char *input_str;
int pos = 0;

struct noeud *lire_prefixe(void)
{

    struct noeud *n = malloc(sizeof(struct noeud));

    while (input_str[pos] == ' ' || input_str[pos] == '(' || input_str[pos] == ')')
    {
        pos++;
    }

    char c = input_str[pos++];
    if (isdigit(c))
    {
        n->code = feuille;
        n->u.valeur = c - '0';
    }
    else if (c == '+' || c == '*')
    {
        n->code = noeud;
        n->u.s.operation = c;
        n->u.s.fils_gauche = lire_prefixe();
        n->u.s.fils_droit = lire_prefixe();
    }

    return n;
}

void ecrire_prefixe(struct noeud *arbre)
{
    if (arbre->code == feuille)
    {
        printf("%d", arbre->u.valeur);
        printf(" ");
    }
    else
    {
        printf("(");
        printf("%c", arbre->u.s.operation);
        printf(" ");
        ecrire_prefixe(arbre->u.s.fils_gauche);
        printf(" ");
        ecrire_prefixe(arbre->u.s.fils_droit);
        printf(")");
    }
}

int profondeur_arbre(struct noeud *arbre)
{
    struct noeud *a = arbre;
    if (arbre == NULL)
    {
        return 0;
    }
    if (!arbre->code == noeud && !arbre->code == feuille)
    {
        return 1;
    }
    else
    {
        int prof_g = profondeur_arbre(arbre->u.s.fils_gauche);
        int prof_d = profondeur_arbre(arbre->u.s.fils_gauche);

        int max_prof;
        if (prof_d > prof_g)
        {
            max_prof = prof_d;
        }
        else
        {
            max_prof = prof_g;
        }

        return (max_prof + 1);
    }
}

int main()
{
    char *buff = NULL;
    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters = getline(&buff, &sizeAllocated, stdin);
    if (buff[characters - 1] == '\n')
    {
        buff[characters - 1] = '\0';
    }

    input_str = buff;

    struct noeud *n = lire_prefixe();
    ecrire_prefixe(n);
    int profondeur = profondeur_arbre(n);
    printf("\nLa profondeur de l'abre est %d\n", profondeur);
    return 0;
}
