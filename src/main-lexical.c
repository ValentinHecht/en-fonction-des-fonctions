/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#include <stdio.h>
#include "lexical.h"

char operation[30];

int main(void)
{
    printf("Entrez votre fonction : ");
    scanf("%s", operation);
    printf("Entrez votre premiere borne : ");
    scanf("%lf", &borneStart);
    printf("Entrez votre deuxieme borne : ");
    scanf("%lf", &borneEnd);

    analyse_lexical(operation);

    return 0;
}