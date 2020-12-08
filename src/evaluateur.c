/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include "evaluateur.h"

#include <math.h>
#include <stdlib.h>

int erreur_eval = 0;
char *cause[];


int get_erreur_evaluateur(){
    return erreur_eval;
}

char get_cause_evaluateur(){
    return &cause[0];
}

float fonc_eval(Node *A, float x)
{
    float y, fils_gauche, fils_droit;
    /* printf("%d\n",A->colonne);
    printf("%d\n",A->couche);
    printf("%f\n",A->jeton.valeur.fonction); */
    
    

    switch (A->jeton.lexem)
    {    
        // Détection d'une fonction        
    case FONCTION:
        y = fonc_eval(A->pjetonpreced, x);
        switch (A->jeton.valeur.fonction)
        {
        case ABS: // Valeur absolue
            
            return abs(y);
            break;

        case SIN: // Sinus
            printf("sin\n");
            return sin(y);
            break;

        case SQRT: //Racine carre
            return sqrt(y);
            break;

        case LOG: // Logarithme
            return log(y);
            break;

        case COS: // Cosinus 
            return cos(y);
            break;

        case TAN: // Tangente
            printf("tan\n");
            return tan(y);
            break;

        case EXP: // Exponentielle
            return expf(y);
            break;

        case ENTIER: // Decimal -> Entier
            return round(y);
            break;

        case VAL_NEG: // Opposé du nombre saisi
            return y * (-1);
            break;
        }

        // Détection d'un opérateur
    case OPERATEUR:
    
        fils_gauche = fonc_eval(A->pjetonpreced, x);
        fils_droit = fonc_eval(A->pjetonsuiv, x);


        switch (A->jeton.valeur.operateur)
        {
        case PLUS: // Addition
            printf("plus\n");
            return fils_gauche + fils_droit;
            break;

        case MOINS: // Soustraction
            return fils_gauche - fils_droit;
            break;

        case FOIS: // Multiplication
        printf("fois\n");
            return fils_gauche * fils_droit;
            break;

        case DIV: // Division
            printf("div\n");
            return fils_gauche / fils_droit;
            break;

        case PUIS: // Puissance
            return pow(fils_gauche, fils_droit);
            break;
        }

        // Détection d'un réel
    case REEL:
        printf("%f\n", A->jeton.valeur.reel);
        return A->jeton.valeur.reel;
        break;

        // Détection d'une variable
    case VARIABLE:
    printf("%f\n",x);
        return x;
        break;
    }
    
}