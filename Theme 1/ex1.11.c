#include <stdio.h>

#define carre(x) ((x) * (x))

int main() {
    printf("carre(5) = %d\n", carre(5));
    printf("carre(2+3) = %d\n", carre(2+3));
    printf("100/carre(5) = %d\n", 100/carre(5));
    printf("carre(x++) = %d\n", carre(5));
    
    return 0;
}