#include <stdio.h>
#include <string.h>

int main() {
    char c = getchar();
    
    int compteur = 0;

    for (int i=0; i<strlen(c); i++) {
        printf("%c", c);
        compteur++;
    }

    return 0;
}