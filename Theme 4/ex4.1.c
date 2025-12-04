#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct couple {
    int num;
    char* string;
};

void afficher_couples (int nb_couples, ...) {
    va_list args;
    va_start(args, nb_couples);
    for (unsigned int i = 0; i < nb_couples;  i++) {
        int num = va_arg(args, int);
        char *str = va_arg(args, char*);
        printf("%s %d\n", str, num);
    }
    va_end(args);
}

int main () {
    int nb_couples = 3;
    afficher_couples(nb_couples, 10, "moi", 20, "toi", 3, "lui");
    return 0;
}