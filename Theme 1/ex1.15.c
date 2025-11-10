#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ecrire_2(unsigned int number)
{
    int i;
    int iterations = 32;

    for (i = iterations - 1; i >= 0; i--)
    {
        if ((number >> i) & 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

int main()
{
    unsigned int number = 16;
    ecrire_2(number);
    return 0;
}