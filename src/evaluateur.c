/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Brossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include "jeton.h";
#include "evaluateur.h";
#include <math.h>


int main(void)
{
    typejeton jeton1;
    jeton1.lexem=REEL;
    jeton1.valeur.reel=1.0f;
    typejeton jeton2;
    jeton2.lexem=OPERATEUR;
    jeton2.valeur.operateur=PLUS;
    typejeton jeton3;
    jeton3.lexem=REEL;
    jeton3.valeur.reel=2;
    Node node;
    node.jeton=jeton2;
    

    return 0;

}

float fonc_eval(Node *A, float x){
    switch (A->jeton.lexem)
    {
    case FONCTION:
    float y = fonc_eval(A->pjetonpreced, x);
       
    //SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC   
        switch (A->jeton.valeur.fonction)
        {
        case ABS:
            return abs(y);
            break;
        
        case SIN:
            return sin(y);
            break;
            
        case SQRT:
            return sqrt(y);
            break;
        
        case LOG:
            return log(y);
            break;
        
        case COS:
            return cos(y);
            break;
        
        case TAN:
            return tan(y);
            break;

        case EXP:
            return expf(y);
            break;

        case ENTIER:
            return round(y);
            break;

        case VAL_NEG:
            return y*(-1);
            break;
        }
    
    case OPERATEUR:
        float fils_gauche = fonc_eval(A->pjetonpreced, x);
        float fils_droit = fonc_eval(A->pjetonsuiv, x);
        
        switch (A->jeton.valeur.operateur)
        {
            case PLUS:
                return fils_gauche+fils_droit;
                break;
            
            case MOINS:
                return fils_gauche-fils_droit;
                break;
            
            case FOIS:
                return fils_gauche*fils_droit;
                break;
            
            case DIV:
                return fils_gauche/fils_droit;
                break;
            
            case PUIS:
                return pow(fils_gauche, fils_droit);
                break;
        }

    case REEL : case VARIABLE:
        return A->jeton.valeur.reel;
        break;

    case ERREUR:
        switch (A->jeton.valeur.erreur)
        {
            case DIV_ZERO: // Division par 0
                return 100;
                break;

            case SQRT_NEG: // Racine nombre negatif
                return 101;
                break;
            
            case PAR_NONFERM: // Parenthese non fermee
                return 102;
                break;

            case PAR_NONOUVER: // Parenthese non ouverte
                return 103;
                break;
            
            case DOUBLE_OPE: // Succession de 2 operateurs
                return 104;
                break;

            case ORTO_FONC: // Mauvaise ecriture de fonction (ex : si au lieu de sin)
                return 105;
                break;
            
            case MAJ_FONC: // defaut de majuscule ou minuscule (SIN et sin uniquement autor)
                return 106;
                break;
            
            case BAR_NONFERME: // Bar d'absolu non ferme
                return 107;
                break;
        }        
    
    }

    
}
