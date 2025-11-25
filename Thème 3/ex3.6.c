#include <stdio.h>

char *mon_strchr(char *chaine, int car){
    unsigned int index = 0;
    while (chaine[index] != '\0') {
        if (chaine[index] == car){
            return index;
        }
        index++;
    }
    return NULL;
}

int main()
{
    char *chaine = "Salut tout le monde";
    char car = 'o';

    char *result = mon_strchr(chaine, car);

    if (result != NULL) {
        // Calculate the position by subtracting the base
        // pointer from the result pointer
        printf("Character '%c' found at position: %d\n",
               car, result);
    }
    else {
        printf("Character '%c' not found.\n", car);
    }
    return 0;

}