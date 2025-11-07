#include <stdio.h>
#include <ctype.h>

int main() {
    int c;
    int lettres[26] = {0};
    
    while ((c = getchar()) != EOF) {
        lettres[c - 'a']++;
    }
    
    printf("\nNombre d'occurrences de chaque lettre :\n");
    for (int i = 0; i < 26; i++) {
        if (lettres[i] > 0) {
            printf("%c : %d\n", 'A' + i, lettres[i]);
        }
    }
    
    return 0;
}