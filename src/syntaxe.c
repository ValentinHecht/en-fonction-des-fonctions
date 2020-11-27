#include <stdio.h>
#include "jeton.h"
int erreur = 0;
char *cause[];

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


Node *syntaxe(Jeton tabJeton[])
{
    typejeton jeton;

    Node *arbre;
    arbre = malloc(sizeof(*arbre));

    int i = 0;
    size_t length = sizeof(tabJeton) / sizeof(tabJeton[0]);

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

    // erreur 109
    typejeton ope_manquant;
    ope_manquant.lexem = OPE_PAR;

    while (i != length)
    {

        // test erreur 100 (division par 0)
        if (tabJeton[i].operateur == DIV && tabJeton[i + 1].reel == 0)
        {
            arbre->jeton.valeur.erreur = DIV_ZERO;
            erreur = 1;
            cause[0]="Une division par 0 est impossible.";
            break;
        }

        // test erreur 102 - 103 (parenthèse)
        if (ouvrir > fermer){
            arbre->jeton.valeur.erreur = PAR_NONFERM;
            erreur = 1;
            cause[0]="Une parenthèse ‘)’ est manquante.";
            break;
        }            

        else if (fermer > ouvrir) {

            arbre->jeton.valeur.erreur = PAR_NONOUVER;
            erreur = 1;
            cause[0]="Une parenthèse ‘(‘ est manquante.";
            break;
        }
            
        // test erreur 104 (double opérande)
        if (tabJeton[i].operateur == tabJeton[i + 1].operateur)
        {
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = DOUBLE_OPE;
            erreur = 1;
            cause[0]="Deux opérateurs sont avoisinants.";
            break;
        }

        // test erreur 107 (Barre non fermée pour val abs)
        if (doublon_absolu % 2 != 0) {

            arbre[i].jeton.valeur.erreur = BAR_ABS;
            erreur = 1;
            cause[0]="Barre d’une valeur absolue est manquante.";
            break;
        }            

        // test erreur 109 parenthèse fermée à côté d'une parenthèse ouverte
        if (tabJeton[i].lexem == tabJeton[i + 1].lexem)
        {

            arbre->jeton.valeur.erreur = OPE_PAR;
            erreur = 1;
            cause[0] = "un opérateur entre parenthèses est manquant.";
            break;
        }

        i++;
    }

    return arbre;
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
    size_t length = sizeof(tab) / sizeof(tab[0]);
    int i;

    arbre = syntaxe(tab);

    for (i = 0; i < length; i++)
    {
        if (arbre->jeton.valeur.erreur == DIV_ZERO)
        {
            printf("erreur 100 : division par zero");
            break;
        }

        if (arbre->jeton.valeur.erreur == PAR_NONOUVER)
        {
            printf("erreur 102 : parenthese non ouverte");
            break;
        }
        else if (arbre->jeton.valeur.erreur == PAR_NONFERM)
        {
            printf("erreur 103 : parenthèse non fermee");
            break;
        }

        if (arbre->jeton.valeur.erreur == DOUBLE_OPE)
        {
            printf("erreur 104 : double operande");
            break;
        }

        if (arbre->jeton.valeur.erreur == BAR_ABS)
        {
            printf("erreur 107 : double barre => valeur absolue non ouverte/ferme");
            break;
        }

        if (arbre->jeton.valeur.erreur == OPE_PAR)
        {
            printf("erreur 109 : opérateur manquant entre parethèses");
            break;
        }
    }

    return 0;
}