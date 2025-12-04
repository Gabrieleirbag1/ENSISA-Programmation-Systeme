#include <stdio.h>
#include "pi.h"

int main () {
    double rayon = 5.0;
    double diametre = surface(rayon);
    double circo = circonference(diametre);

    printf("Circonférence du cercle : %f \n", circo);

    return 0;
}