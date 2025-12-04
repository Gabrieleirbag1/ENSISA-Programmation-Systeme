#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mystruct
{
    char *car;
    int tableau[10];
    struct mystruct *testStruct;
};
typedef struct mystruct mystruct;

int main()
{
    struct mystruct *table[50];
    return 0;
}