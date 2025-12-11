   #include <stdio.h>

   int main() {
       printf("Size of int: %zu bytes\n", sizeof(int));
       printf("Size of char: %zu bytes\n", sizeof(char));
       printf("Size of char *: %zu bytes\n", sizeof(char *));
       struct { char c; char *pc; int i; } s;
       printf("Size of struct { char c; char *pc; int i; }: %zu bytes\n", sizeof(s));
       printf("Size of struct { char c; char *pc; int i; } *: %zu bytes\n", sizeof(struct { char c; char *pc; int i; } *));
       return 0;
   }