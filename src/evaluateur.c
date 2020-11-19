/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include "jeton.h"
#include "evaluateur.h"
#include <math.h>

#define borne_min -10
#define borne_sup 10

int error = 0; // Si detection d'une erreur -> = 1
char *cause []; // Si erreur = 1 -> indiquer la cause et stopper le traitement (sauf graphique)

int main(void)
{

    typejeton jeton1;
    jeton1.lexem = OPERATEUR;
    jeton1.valeur.operateur=PLUS;
    typejeton jeton2;
    jeton2.lexem = FONCTION;
    jeton2.valeur.operateur = SIN;
    typejeton jeton3;
    jeton3.lexem = VARIABLE;
    typejeton jeton4;
    jeton4.lexem=REEL;
    jeton4.valeur.reel=12;

    Noeud noeud_2;
    noeud_2.jeton=jeton2;
    noeud_2.pjetonpreced=&jeton3;


    Noeud noeud_1;
    noeud_1.jeton=jeton1;
    noeud_1.pjetonpreced=&noeud_2;
    noeud_1.pjetonsuiv=&jeton4;

    // Pour modifier la cause : cause[0] = 'lol';
    // Pour indiquer qu'il  y a une erreur error = 1;

    float couples[200][2];
    int tab_compteur = 0;
    if(!error){
        for (float i = borne_min; i <= borne_sup; i++)
        {
            couples[tab_compteur][0] = i;                       // Valeurs de x
            couples[tab_compteur][1] = fonc_eval(&noeud_1, i);  // Valeurs de f(x)
            tab_compteur++;
        }
        for (int i = 0; i < tab_compteur; i++)
        {
            printf("Valeur de x    : %f\n", couples[i][0]);
            printf("Valeur de f(x) : %f\n", couples[i][1]);
            printf("\n");
        }
    }
    else{
        printf("%s\n", &cause[0]);
    }
    return 0;
}

float fonc_eval(Noeud *A, float x)
{
    float y, fils_gauche, fils_droit;

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
        fils_gauche = fonc_eval(A->pjetonpreced, x);
        fils_droit = fonc_eval(A->pjetonsuiv, x);

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
        return x;
        break;
    }
}
