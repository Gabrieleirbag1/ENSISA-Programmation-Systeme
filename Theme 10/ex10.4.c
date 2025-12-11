#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h> /* lseek, write, close */
#include <string.h> /* memcpy, memchr */
#include <stdlib.h> /* exit */

int main(int argc, char *argv[])
{
    int fdin;
    char *src;
    struct stat statbuf;

    if (argc != 2)
    {
        printf("Usage: a.out <fromfile>\n");
        return 1;
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0)
    {
        printf("Can't open %s for reading\n", argv[1]);
        return 1;
    }

    if (fstat(fdin, &statbuf) < 0)
    {
        printf("fstat error\n");
        close(fdin);
        return 1;
    }

    if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
    {
        printf("mmap error for input\n");
        close(fdin);
        return 1;
    }

    char *first_newline = memchr(src, '\n', statbuf.st_size);
    if (first_newline)
    {
        size_t first_len = first_newline - src + 1;
        printf("First line of %s: %.*s", argv[1], (int)first_len, src);
    }

    if (statbuf.st_size > 0)
    {
        char *last_newline = NULL;
        char *ptr = src;
        while ((ptr = memchr(ptr, '\n', statbuf.st_size - (ptr - src))))
        {
            last_newline = ptr;
            ptr++;  // Avancer après le \n trouvé
        }
        if (last_newline)
        {
            // Dernière ligne : de last_newline+1 à la fin
            size_t last_len = (src + statbuf.st_size) - (last_newline + 1);
            printf("Last line of %s: %.*s \n", argv[1], (int)last_len, last_newline + 1);
        }
    }

    return 0;
}