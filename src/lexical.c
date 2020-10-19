/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "jeton.h"
#include "lexical.h"

int i = 0;
int jeton = 0;

Jeton jetons[25];

char* analyse_lexical(char* op)  {
    //printf("Vous avez ecrit : ");

    while(op[i] != '\0') {
        //printf("%c", op[i]);


        //////////////////////// RECHERCHE D'UNE VARIABLE ////////////////////////

        if (isalpha(op[i]) && !isalpha(op[i+1])) {  
            printf("Variable detecte ! : %c \n", op[i]);
            Jeton jetonvar;
            jetonvar.var = op[i];
            jetonvar.lexem = VARIABLE;
            jetons[jeton] = jetonvar;
            jeton++;
            i++;            
        }
        
        //////////////////////// RECHERCHE DES FONCTIONS ////////////////////////
        
        else if ((op[i] == 's' && op[i+1] == 'i' && op[i+2] == 'n') || (op[i] == 'S' && op[i+1] == 'I' && op[i+2] == 'N')) {
            puts("Fonction SIN detecte !");
            Jeton jetonsin;
            jetonsin.lexem = FONCTION;
            jetonsin.fonction = SIN;
            jetons[jeton] = jetonsin;
            jeton++;
            i = i+3;
        } else if ((op[i] == 'c' && op[i+1] == 'o' && op[i+2] == 's') || (op[i] == 'C' && op[i+1] == 'O' && op[i+2] == 'S')) {
            puts("Fonction COS detecte !");
            Jeton jetonsicos;
            jetonsicos.lexem = FONCTION;
            jetonsicos.fonction = COS;
            jetons[jeton] = jetonsicos;
            jeton++;
            i = i+3;
        } else if ((op[i] == 's' && op[i+1] == 'q' && op[i+2] == 'r' && op[i+3] == 't') || (op[i] == 'S' && op[i+1] == 'Q' && op[i+2] == 'R' && op[i+3] == 'T')) {
            puts("Fonction SQRT detecte !");
            Jeton jetonsqrt;
            jetonsqrt.lexem = FONCTION;
            jetonsqrt.fonction = SQRT;
            jetons[jeton] = jetonsqrt;
            jeton++;
            i = i+4;
        } else if ((op[i] == 'l' && op[i+1] == 'o' && op[i+2] == 'g') || (op[i] == 'L' && op[i+1] == 'O' && op[i+2] == 'G')) {
            puts("Fonction LOG detecte !");
            Jeton jetonlog;
            jetonlog.lexem = FONCTION;
            jetonlog.fonction = LOG;
            jetons[jeton] = jetonlog;
            jeton++;
            i = i+3;
        } else if ((op[i] == 't' && op[i+1] == 'a' && op[i+2] == 'n') || (op[i] == 'T' && op[i+1] == 'A' && op[i+2] == 'N')) {
            puts("Fonction TAN detecte !");
            Jeton jetontan;
            jetontan.lexem = FONCTION;
            jetontan.fonction = TAN;
            jetons[jeton] = jetontan;
            jeton++;
            i = i+3;
        } else if ((op[i] == 'e' && op[i+1] == 'x' && op[i+2] == 'p') || (op[i] == 'E' && op[i+1] == 'X' && op[i+2] == 'P')) {
            puts("Fonction EXP detecte !");
            Jeton jetonexp;
            jetonexp.lexem = FONCTION;
            jetonexp.fonction = EXP;
            jetons[jeton] = jetonexp;
            jeton++;
            i = i+3;
        } else if ((op[i] == 'e' && op[i+1] == 'n' && op[i+2] == 't' && op[i+2] == 'i' && op[i+2] == 'e' && op[i+2] == 'r') || (op[i] == 'E' && op[i+1] == 'N' && op[i+2] == 'T' && op[i+2] == 'I' && op[i+2] == 'E' && op[i+2] == 'R')) {
            puts("Fonction ENTIER detecte !");
            Jeton jetonentier;
            jetonentier.lexem = FONCTION;
            jetonentier.fonction = ENTIER;
            jetons[jeton] = jetonentier;
            jeton++;
            i = i+6;
        } else if ((op[i] == 'v' && op[i+1] == 'a' && op[i+2] == 'l' && op[i+2] == '_' && op[i+2] == 'n' && op[i+2] == 'e' && op[i+2] == 'g') || (op[i] == 'V' && op[i+1] == 'A' && op[i+2] == 'L' && op[i+2] == '_' && op[i+2] == 'N' && op[i+2] == 'E' && op[i+2] == 'G')) {
            puts("Fonction VAL_NEG detecte !");
            Jeton jetonvalneg;
            jetonvalneg.lexem = FONCTION;
            jetonvalneg.fonction = VAL_NEG;
            jetons[jeton] = jetonvalneg;
            jeton++;
            i = i+7;
        }
        
        //////////////////////// RECHERCHE DES PARENTHESES ////////////////////////
        
        else if (op[i] == '(') {
            puts("Parenthese ouvrante detecte !");
            Jeton jetonparouvr;
            jetonparouvr.lexem = PAR_OUV;
            jetons[jeton] = jetonparouvr;
            jeton++;
            i++;
        } else if (op[i] == ')') {
            puts("Parenthese fermante detecte !");
            Jeton jetonparfermr;
            jetonparfermr.lexem = PAR_FERM;
            jetons[jeton] = jetonparfermr;
            jeton++;
            i++;
        } 
        
        //////////////////////// RECHERCHE DES CHIFFRES ////////////////////////
        
        else if (isdigit(op[i])) {
            int y = i;
            int indice = 0;
            char tabreel[10];
            int test;
            while(isdigit(op[y]) || op[y] == '.') {
                printf("Variable detecte (ou virgule) ! : %c \n", op[y]);
                tabreel[indice] = op[y];
                y++;
                indice++;
            }

            Jeton jetonvar;
            jetonvar.lexem = VARIABLE;
            jetonvar.reel = atof(tabreel);
            jetons[jeton] = jetonvar;
            i+= indice;
            jeton++;
        }
        
        //////////////////////// RECHERCHE DES OPERATEURS ////////////////////////
        
        else if (op[i] == '+' || op[i] == '-' || op[i] == '*' || op[i] == '/' || op[i] == '^') {
            printf("Operateur detecte ! : %c \n", op[i]);
            Jeton jetonoperateur;
            jetonoperateur.lexem = OPERATEUR;
            if (op[i] == '+') {
                jetonoperateur.operateur = PLUS;
            } else if (op[i] == '-') {
                jetonoperateur.operateur = MOINS;
            } else if (op[i] == '*') {
                jetonoperateur.operateur = FOIS;
            } else if (op[i] == '/') {
                jetonoperateur.operateur = DIV;
            } else {
                jetonoperateur.operateur = PUIS;
            }
            jetons[jeton] = jetonoperateur;
            i++;
            jeton++;
        } else if (isspace(op[i])) {
            puts("Espace detecte !");
            i++;
        } else {
            puts("ERREUR");
            i++;
        }

    }

    puts("FIN detecte !");

    for(int u = 0; u !=3; u++){
        printf("%i", jetons[u].lexem);
    }


    return op;
};

