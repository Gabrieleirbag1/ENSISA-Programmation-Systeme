#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void copyfile(char *content, int index)
{
    FILE *fp2;
    fp2 = fopen("archive", "w");
    if (fp2 != NULL)
    {
        for (int i = 0; i < index; i++)
        {
            putc(content[i], fp2);
        }
        fclose(fp2);
    }
    else
    {
        printf("Error opening file!");
    }
}

void readfiles(char *file, char *content, int *index)
{
    FILE *fp;
    fp = fopen(file, "r");
    char c;
    if (fp != NULL)
    {
        while ((c = getc(fp)) != EOF)
        {
            content[(*index)++] = c;
        }
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "nt:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            printf("s");
            break;
        }
    }

    char content[1000];
    int index = 0;

    char files[10][10] = {"basile", "vasile"};
    int num_files = sizeof(files) / sizeof(files[0]);
    for (int i = 0; i < num_files; i++) {
        if (files[i][0] == '\0') break;
        readfiles(files[i], content, &index);
    }
    
    copyfile(content, index);
    
    return 0;
}