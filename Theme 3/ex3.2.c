#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int numbers[], int *index)
{
    for (unsigned int i = 0; i < *index - 1; i++)
    {
        for (unsigned int j = i + 1; j < *index; j++)
        {
            if (numbers[i] > numbers[j])
            {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}

int main()
{
    int numbers[1000];
    char *buff = NULL;
    int index = 0;

    size_t sizeAllocated = 0;
    printf("> ");
    size_t characters;

    while ((characters = getline(&buff, &sizeAllocated, stdin)) != EOF)
    {
        int number = atoi(buff);
        numbers[index++] = number;

        sort(numbers, &index);

        printf("Converted %d\n", number);
    }
    numbers[index] = '\0';

    int sizeNumbers = sizeof(numbers) / sizeof(numbers[0]);
    for (unsigned int i = 0; i < sizeNumbers; i++)
    {
        if (numbers[i] == '\0')
            break;
        printf("|");
        printf("%d", numbers[i]);
    }

    free(buff);
    buff = NULL;

    printf("\n");
    return 0;
}