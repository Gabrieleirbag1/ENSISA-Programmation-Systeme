#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("toto", "r");
    char c;
    char content[1000];
    int index = 0;
    if (fp != NULL)
    {
        while ((c = getc(fp)) != EOF)
        {
            putc(c, stdout);
            content[index++] = c;
        }
        fclose(fp);
    }
    else
    {
        printf("Error opening file!");
    }

    FILE *fp2;
    fp2 = fopen("titi", "w");
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
    printf("\n");
    return 0;
}