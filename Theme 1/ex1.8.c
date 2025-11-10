#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct mois
{
    char nom[1024];
    int jours;
};

int main()
{   
    const struct mois janvier = {"janvier", 31};
    const struct mois fevrier = {"février", 28};
    const struct mois mars = {"mars", 31};
    const struct mois avril = {"avril", 30};
    const struct mois mai = {"mai", 31};
    const struct mois juin = {"juin", 30};
    const struct mois juillet = {"juillet", 31};
    const struct mois aout = {"août", 31};
    const struct mois septembre = {"septembre", 30};
    const struct mois octobre = {"octobre", 31};
    const struct mois novembre = {"novembre", 30};
    const struct mois decembre = {"décembre", 31};

    const struct mois allMois[] = {janvier, fevrier, mars, avril, mai, juin, juillet, aout, septembre, octobre, novembre, decembre};
    
    char string_input[1024] = "";
    char c;
    int index = 0;
    while ((c = getchar()) != '\n' && c != EOF && index < 1023) {
        string_input[index++] = c;
    }
    string_input[index] = '\0';

    int nbMois = sizeof(allMois) / sizeof(allMois[0]);
    int isMonth = 0;

    for (int i = 0; i < nbMois; i++){
        for(int i = 0; string_input[i]; i++){
            string_input[i] = tolower(string_input[i]);
        }
        if (!strcmp(allMois[i].nom, string_input)){
            isMonth = 1;
        }
    }

    if (!isMonth) {
        printf("%s is not a month bro \n", string_input);
    }
    
    return 0;
}