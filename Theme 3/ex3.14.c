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
    else if (c == '+' || c == '*' || c == '-' || c == '/')
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
        int prof_d = profondeur_arbre(arbre->u.s.fils_droit);

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

int ajouter(int a, int b)
{
    return a + b;
}

int soustraire(int a, int b)
{
    return a - b;
}

int multiplier(int a, int b)
{
    return a * b;
}

int diviser(int a, int b)
{
    return a / b;
}

int (*operations[])(int, int) = {ajouter, soustraire, multiplier, diviser};

int evaluer_arbre(struct noeud *arbre)
{
    if (arbre->code == feuille)
    {
        return arbre->u.valeur;
    }
    else if (arbre->code == noeud)
    {
        char operation = arbre->u.s.operation;
        int val_g = evaluer_arbre(arbre->u.s.fils_gauche);
        int val_d = evaluer_arbre(arbre->u.s.fils_droit);
        switch (operation)
        {
        case '+':
            return (*operations[0])(val_g, val_d);
        case '-':
            return (*operations[1])(val_g, val_d);
        case '*':
            return (*operations[2])(val_g, val_d);
        case '/':
            return (*operations[3])(val_g, val_d);
        }
    }
}

void ecrire_algebrique(struct  noeud *arbre)
{
    if (arbre->code == feuille)
    {
        printf("%d", arbre->u.valeur);
        printf(" ");
    }
    else
    {
        printf("(");
        printf(" ");
        ecrire_algebrique(arbre->u.s.fils_gauche);
        printf("%c", arbre->u.s.operation);
        printf(" ");
        ecrire_algebrique(arbre->u.s.fils_droit);
        printf(")");
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
    printf("\n");
    ecrire_algebrique(n);
    int profondeur = profondeur_arbre(n);
    int valeur = evaluer_arbre(n);
    printf("\nLa profondeur de l'arbre est %d\n", profondeur);
    printf("La valeur de l'expression est %d\n", valeur);
    return 0;
}
