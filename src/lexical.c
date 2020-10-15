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


        //////////////////////// RECHERCHE D'UNE VARIABLE ////////////////////////

        if (isalpha(op[i]) && !isalpha(op[i+1])) {  
            printf("Variable detecte ! : %c \n", op[i]);
            i++;            
        }
        
        //////////////////////// RECHERCHE DES FONCTIONS ////////////////////////
        
        else if ((op[i] == 's' && op[i+1] == 'i' && op[i+2] == 'n') || (op[i] == 'S' && op[i+1] == 'I' && op[i+2] == 'N')) {
            puts("Fonction SIN detecte !");
            i = i+3;
        } else if ((op[i] == 'c' && op[i+1] == 'o' && op[i+2] == 's') || (op[i] == 'C' && op[i+1] == 'O' && op[i+2] == 'S')) {
            puts("Fonction COS detecte !");
            i = i+3;
        } else if ((op[i] == 's' && op[i+1] == 'q' && op[i+2] == 'r' && op[i+3] == 't') || (op[i] == 'S' && op[i+1] == 'Q' && op[i+2] == 'R' && op[i+3] == 'T')) {
            puts("Fonction SQRT detecte !");
            i = i+4;
        } else if ((op[i] == 'l' && op[i+1] == 'o' && op[i+2] == 'g') || (op[i] == 'L' && op[i+1] == 'O' && op[i+2] == 'G')) {
            puts("Fonction LOG detecte !");
            i = i+3;
        } else if ((op[i] == 't' && op[i+1] == 'a' && op[i+2] == 'n') || (op[i] == 'T' && op[i+1] == 'A' && op[i+2] == 'N')) {
            puts("Fonction TAN detecte !");
            i = i+3;
        } else if ((op[i] == 'e' && op[i+1] == 'x' && op[i+2] == 'p') || (op[i] == 'E' && op[i+1] == 'X' && op[i+2] == 'P')) {
            puts("Fonction EXP detecte !");
            i = i+3;
        } else if ((op[i] == 'e' && op[i+1] == 'n' && op[i+2] == 't' && op[i+2] == 'i' && op[i+2] == 'e' && op[i+2] == 'r') || (op[i] == 'E' && op[i+1] == 'N' && op[i+2] == 'T' && op[i+2] == 'I' && op[i+2] == 'E' && op[i+2] == 'R')) {
            puts("Fonction ENTIER detecte !");
            i = i+6;
        } else if ((op[i] == 'v' && op[i+1] == 'a' && op[i+2] == 'l' && op[i+2] == '_' && op[i+2] == 'n' && op[i+2] == 'e' && op[i+2] == 'g') || (op[i] == 'V' && op[i+1] == 'A' && op[i+2] == 'L' && op[i+2] == '_' && op[i+2] == 'N' && op[i+2] == 'E' && op[i+2] == 'G')) {
            puts("Fonction VAL_NEG detecte !");
            i = i+7;
        }
        
        //////////////////////// RECHERCHE DES PARENTHESES ////////////////////////
        
        else if (op[i] == '(') {
            puts("Parenthese ouvrante detecte !");
            i++;
        } else if (op[i] == ')') {
            puts("Parenthese fermante detecte !");
            i++;
        } 
        
        //////////////////////// RECHERCHE DES CHIFFRES ////////////////////////
        
        else if (isdigit(op[i])) {
            printf("Variable detecte ! : %c \n", op[i]);
            i++;

            while (isdigit(op[i])) {
                printf("Variable detecte ! : %c \n", op[i]);
                i++;
            }
        }
        
        //////////////////////// RECHERCHE DES OPERATEURS ////////////////////////
        
        else if (op[i] == '+' || op[i] == '-' || op[i] == '*' || op[i] == '/' || op[i] == '^') {
            printf("Operateur detecte ! : %c \n", op[i]);
            i++;
        } else if (op[i] == ' ') {
            puts("Espace detecte !");
            i++;
        } else {
            puts("ERREUR");
            i++;
        }

    }

    puts("FIN detecte !");

    return op;
};

