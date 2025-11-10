#include <stdio.h>

int factorielle(int n)
{
    int f;
    if (n <= 1)
        f = 1;
    else 
        f = n * factorielle(n-1);
    return f;
}

int main()
{   
    int test = 4;
    int test2 = factorielle(test);
    printf("factorielle(%d) = %d\n", test, test2);
    return 0;
}