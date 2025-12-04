#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read(char *string) {
    char tableau[100][100];
    int j = 0;
    int k = 0;
    for (unsigned int i = 0; i < strlen(string); i++) {
        char c = string[i];
        if (c == ':') {
            tableau[k][j+1] = '\0';
            k++;
            j = 0;
            continue;
        }
        tableau[k][j] = c;
        j++;
    }

    // show table
    for (int i = 0; i <= k; i++) {
        printf("%s\n", tableau[i]);
    }

}

int main()
{
    char * path = getenv( "PATH" );
    read(path);

    return 0;
}