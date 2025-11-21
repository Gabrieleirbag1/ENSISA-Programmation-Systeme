#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    fp = fopen("file", "r");
    char c;
    char content[1000];
    int index = 0;
    if (fp != NULL)
    {
        while ((c = getc(fp)) != EOF)
        {
            content[index++] = c;
        }
        fclose(fp);
    }
    printf("\n");
    content[index] = '\0';

    char final_string[1000];

    int nb_lines = 10;
    int count = 0;
    size_t i = strlen(content);
    for (i; i != 0; i--) {
        if (nb_lines == 0) {
            break;
        }
        
        count = final_string[-i + strlen(content) + 1] = content[i];

        if (content[i] == '\n') {
            nb_lines--;
        }
    }
    final_string[strlen(content) - i + 1] = '\0';
    
    for (unsigned int i; i < strlen(content); i++) {
        putc(content[i], stdout);
    }
    return 0;
}