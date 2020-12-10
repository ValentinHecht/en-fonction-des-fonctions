/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include <stdio.h>
#include "erreur_syntaxe.h"
#include <stdlib.h>

void test_erreur(Jeton tabJeton[], int elem, Node *arbre)
{

    int i = 0;
    // erreur 102-103
    typejeton ouverte;
    ouverte.lexem = PAR_OUV;
    int ouvrir = contains(tabJeton, ouverte, elem);
    typejeton ferme;
    ferme.lexem = PAR_FERM;
    int fermer = contains(tabJeton, ferme, elem);
    printf("test 1 : %d\n", ouvrir);
    printf("test 2 : %d\n", fermer);
    // erreur 104
    typejeton double_ope;
    double_ope.lexem = OPERATEUR;
    typejeton erreur_ope;
    // erreur 107
    typejeton barre;
    barre.lexem = BARRE;
    int doublon_absolu = contains(tabJeton, barre, elem);
    // erreur 109
    typejeton ope_manquant;
    ope_manquant.lexem = OPE_PAR;
    while (i != elem)
    {
        // test erreur 100 (division par 0)
        if (tabJeton[i].operateur == DIV && tabJeton[i + 1].reel == 0)
        {
            arbre->jeton.valeur.erreur = DIV_ZERO;
            erreur_syntax = 1;
            cause[0] = "Une division par 0 est impossible.";
            break;
        }
        // test erreur 102 - 103 (parenthèse)
        if (ouvrir > fermer)
        {
            arbre->jeton.valeur.erreur = PAR_NONFERM;
            erreur_syntax = 1;
            printf("test 3 : %d\n", fermer);
            printf("test 4 : %d\n", ouvrir);
            cause[0] = "Une parenthèse ')' est manquante.";
            break;
        }
        else if (fermer > ouvrir)
        {
            arbre->jeton.valeur.erreur = PAR_NONOUVER;
            erreur_syntax = 1;
            cause[0] = "Une parenthèse '(' est manquante.";
            break;
        }
        // test erreur 104 (double opérande)
        if ((tabJeton[i].lexem == OPERATEUR) && (tabJeton[i + 1].lexem == OPERATEUR))
        {
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = DOUBLE_OPE;
            erreur_syntax = 1;
            cause[0] = "Deux opérateurs sont avoisinants.";
            break;
        }
        // test erreur 107 (Barre non fermée pour val abs)
        if (doublon_absolu % 2 != 0)
        {
            arbre[i].jeton.valeur.erreur = BAR_ABS;
            erreur_syntax = 1;
            cause[0] = "Barre d’une valeur absolue est manquante.";
            break;
        }
        // test erreur 109 parenthèse fermée à côté d'une parenthèse ouverte
        if ((tabJeton[i].lexem == PAR_FERM) && (tabJeton[i + 1].lexem == PAR_OUV))
        {
            arbre->jeton.valeur.erreur = OPE_PAR;
            erreur_syntax = 1;
            cause[0] = "un opérateur entre parenthèses est manquant.";
            break;
        }
        i++;
    }
}