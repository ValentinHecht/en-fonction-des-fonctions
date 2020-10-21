#include <stdio.h>
#include "jeton.h"

Node *syntaxe(Jeton tabJeton[])
{

    // sin(x+2)
    // sin(x++3))
    // doiqsnd(x+3)

    // fonction, variable, opérande, réel



    typejeton jeton;

    Node *arbre;
    arbre = malloc(sizeof(*arbre));

    int i = 0;
    size_t length = sizeof(tabJeton)/sizeof(tabJeton[0]);

    // erreur 102-103
    typejeton ouverte;
    ouverte.lexem = PAR_OUV;
    int ouvrir = contains(tabJeton, ouverte);
    typejeton ferme;
    ferme.lexem = PAR_FERM;
    int fermer = contains(tabJeton, ferme);

    // erreur 104
    typejeton double_ope;
    double_ope.lexem = OPERATEUR;
    typejeton erreur_ope;

    // erreur 107
    typejeton barre;
    barre.lexem = BARRE;
    int doublon_absolu = contains(tabJeton, ouverte);

    while (i != length)
    {

        // Au début de la boucle, ajoute dans l'arbre le suivant

        // test erreur 100 (division par 0)
        if (tabJeton[i].operateur == DIV && tabJeton[i + 1].reel == 0)
        {
            arbre->jeton.valeur.erreur = DIV_ZERO;
        }

        // test erreur 102 - 103 (parenthèse)
        if (ouvrir > fermer)
            arbre->jeton.valeur.erreur = PAR_NONFERM;
        else if (fermer > ouvrir)
            arbre->jeton.valeur.erreur = PAR_NONOUVER;

        // test erreur 104 (double opérande)
        if (tabJeton[i].operateur == tabJeton[i + 1].operateur)
        {
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = DOUBLE_OPE;
        }

        // test erreur 107 (Barre non fermée pour val abs)
        if (doublon_absolu % 2 != 0)
            arbre[i].jeton.valeur.erreur = BAR_ABS;

        i++;
    }

    return arbre;
}

int contains(Jeton tab[], typejeton jeton)
{
    int occ = 0;

    for (int i = 0; i < sizeof(tab); i++)
    {
        if (tab[i].lexem == jeton.lexem)
        {
            occ++;
        }
        else if (tab[i].operateur == jeton.valeur.operateur)
        {
            occ++;
        }
    }

    return occ;
}

int main()
{
    // test tab
    Jeton tab[5];
    tab[0].lexem = BARRE;
    tab[1].lexem = PAR_OUV;
    tab[2].lexem = REEL;
    tab[3].lexem = PAR_FERM;
    tab[4].lexem = BARRE;


    Node *arbre;
    size_t length = sizeof(tab)/sizeof(tab[0]);
    int i;

    arbre = syntaxe(tab);

    
    for (i = 0; i < length; i++)
    {
        if (arbre->jeton.valeur.erreur == DIV_ZERO)
        {
            printf("erreur 100 : division zero");
            break;
        }

        if (arbre->jeton.valeur.erreur == PAR_NONOUVER)
        {
            printf("erreur 102 : parenthese non ouverte");
            break;
        }
        else if (arbre->jeton.valeur.erreur == PAR_NONFERM)
        {
            printf("erreur 103 : parenthèse non ferme");
            break;
        }

        if (arbre->jeton.valeur.erreur == DOUBLE_OPE)
        {
            printf("erreur 104 : double operande");
            break;
        }

        if (arbre->jeton.valeur.erreur == BAR_ABS)
        {
            printf("erreur 107 : double barre => valeur absolue non ouverte/ ferme");
            break;
        }
    }

    if (i == length) printf("OK !");

    printf("\n\n\nFin du programme...\n\n");

    return 0;
}

// précédent :
// suivant :

// Retourner le jeton d'erreur