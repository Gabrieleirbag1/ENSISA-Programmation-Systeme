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
            struct noeud *fils_gauche;
            struct noeud *fils_droit;
        } s;
    } u;
};

struct noeud *lire_prefixe(void)
{

    struct noeud *n = malloc(sizeof(struct noeud));

    char *buff = NULL;
    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters = getline(&buff, &sizeAllocated, stdin);
    if (buff[characters - 1] == '\n') {
        buff[characters - 1] = '\0';
    }

    for (unsigned int i = 0; i < strlen(buff); i++)

    {
        char c = buff[i];
        if (c == ' ') continue;
        if (isdigit(c))
        {
            n->code = feuille;
            n->u.valeur = c - '0';
        }
        else if (c == '+' || c == '*')
        {
            n->code = noeud;
            n->u.s.fils_gauche = lire_prefixe();
            n->u.s.fils_droit = lire_prefixe();
        }
    }

    return n;
}

int main()
{
    lire_prefixe();
    return 0;
}