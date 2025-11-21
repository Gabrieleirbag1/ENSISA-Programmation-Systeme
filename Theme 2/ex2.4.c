#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int opt;
    int nb_lines = 10;

    while ((opt = getopt(argc, argv, "nt:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            nb_lines = atoi(argv[2]);
            break;
        }
    }

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

    size_t len = strlen(content);
    size_t start_pos = len;
    
    // Find starting position (counting newlines from end)
    int lines_found = 0;
    for (size_t i = len; i > 0; i--)
    {
        if (content[i - 1] == '\n')
        {
            lines_found++;
            if (lines_found == nb_lines)
            {
                start_pos = i;
                break;
            }
        }
    }
    if (lines_found < nb_lines) {
        start_pos = 0;
    }

    size_t j = 0;
    for (size_t i = start_pos; i < len; i++)
    {
        final_string[j++] = content[i];
    }
    final_string[j] = '\0';

    printf("%s", final_string);

    return 0;
}