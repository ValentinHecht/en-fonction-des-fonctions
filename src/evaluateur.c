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

float fonc_eval(Arbre A, float x)
{
    float y, fils_gauche, fils_droit;


    switch (A->jeton.lexem)
    {    
        // Détection d'une fonction        
    case FONCTION:
        printf("fonctyion");
        y = fonc_eval(A->pjetonpreced, x);
        switch (A->jeton.valeur.fonction)
        {
        case ABS: // Valeur absolue
            printf("abs");
            return abs(y);
            break;

        case SIN: // Sinus
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
        printf("\nsdfsdf\n");
        printf("\ncouche: %d\n", A->couche);
        printf("colonne: %d\n", A->colonne);
        fils_gauche = fonc_eval(A->pjetonpreced, x);
        fils_droit = fonc_eval(A->pjetonsuiv, x);
        printf("\ncouche droit: %d\n", A->pjetonsuiv->jeton.valeur);
        printf("colonne droit: %d\n", A->pjetonsuiv->jeton.valeur);
        printf("\ncouche gauche: %d\n", A->pjetonpreced->jeton.valeur);
        printf("colonne gauche: %d\n", A->pjetonpreced->jeton.valeur);

        switch (A->jeton.valeur.operateur)
        {
        case PLUS: // Addition
            return fils_gauche + fils_droit;
            break;

        case MOINS: // Soustraction
            return fils_gauche - fils_droit;
            break;

        case FOIS: // Multiplication
            return fils_gauche * fils_droit;
            break;

        case DIV: // Division
            return fils_gauche / fils_droit;
            break;

        case PUIS: // Puissance
            return pow(fils_gauche, fils_droit);
            break;
        }

        // Détection d'un réel
    case REEL:
        return A->jeton.valeur.reel;
        break;

        // Détection d'une variable
    case VARIABLE:
        printf("%f\n",x);
        return x;
        break;
    }
}