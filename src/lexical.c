/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "jeton.h"
#include "lexical.h"

int i = 0;

char* analyse_lexical(char* op)  {
    //printf("Vous avez ecrit : ");

    while(op[i] != '\0') {
        //printf("%c", op[i]);

        if ((op[i] == 's' && op[i+1] == 'i' && op[i+2] == 'n') || (op[i] == 'S' && op[i+1] == 'I' && op[i+2] == 'N')) {
            puts("Fonction SIN detecte !");
            i = i+3;
        } else if ((op[i] == 's' && op[i+1] == 'q' && op[i+2] == 'r' && op[i+3] == 't') || (op[i] == 'S' && op[i+1] == 'Q' && op[i+2] == 'R' && op[i+3] == 'T')) {
            puts("Fonction SQRT detecte !");
            i = i+4;
        } else if (op[i] == '(') {
            puts("Parenthese ouvrante detecte !");
            i++;
        } else if (op[i] == ')') {
            puts("Parenthese fermante detecte !");
            i++;
        } else if (isdigit(op[i])) {
            puts("Chiffre detecte !");
            i++;
        } else {
            i++;
        }

    }

    return op;
};

