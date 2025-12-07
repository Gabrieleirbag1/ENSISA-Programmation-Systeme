#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main (int argc, char *argv[]) {
    FILE *fp;
    char buffer[256];

    char n;
    char *p = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [section] page_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (isdigit(argv[1][0])) {
        n = argv[1][0];
        p = argv[2];
    } else {
        p = argv[1];
        n = '1';
    }

    char command[512];
    sprintf(command, "gunzip < /usr/share/man/man%c/%s.%c.gz | nroff -man", n, p, n);

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    
    // Close the pipe
    if (pclose(fp) == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}