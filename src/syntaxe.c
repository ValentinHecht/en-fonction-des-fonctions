#include <stdio.h>
#include "jeton.h"

int is_inPar(int debut[], int fin[], int pos) {
    // On suppose que debut.length == fin.length
    size_t length = sizeof(debut)/sizeof(debut[0]);

    for (int i = 0; i < length; i++) {
        // c'est dans la parenthese/fonction
        if (debut[i] < pos && pos < fin[i]) {
            return 0;
        }
    }
    
    return 1;
}


void create_tree(Jeton tabJeton[]) {
    Node *arbre;
    Node *nodeActuel;

    arbre = malloc(sizeof(*arbre));

    int debut_fonction[5];
    int fin_fonction[5];
    int df = 0;
    int ff = 0;

    int debut_parenthese[10];
    int fin_parenthese[10];
    int dp = 0;
    int fp = 0;

    int operande[20];
    int o = 0;

    int reel[40];
    int r = 0;

    int var[20];
    int v = 0;

    size_t length = sizeof(tabJeton)/sizeof(tabJeton[0]);

    Jeton tab [10][20][length];

    // Récupère les positions de tout les jetons
    for (int i = 0; i < length; i++) {
        if (tabJeton[i].lexem == FONCTION) debut_fonction[df] = i, df++;
        if (tabJeton[i].lexem == PAR_OUV) debut_parenthese[dp] = i, dp++;
        if (tabJeton[i].lexem == PAR_FERM) fin_parenthese[fp] = i, fp++;
        if (tabJeton[i].lexem == PAR_FERM && dp == fp) fin_fonction[ff] = i, ff++;

        if (tabJeton[i].lexem == OPERATEUR) operande[v] = i, o++;
        if (tabJeton[i].lexem == REEL) reel[v] = i, r++;
        if (tabJeton[i].lexem == VARIABLE) var[v] = i, v++;

        tab[0][0][i] = tabJeton[i];
    }


    // On crée le premier node de l'arbre
    arbre->couche = 0;
    arbre->colonne = 0;
    arbre->pjetonparent = -1;
    // si l'expression ne contient qu'une fonction..
    if (fin_fonction[0] == length) {
        arbre->jeton.lexem == tabJeton[debut_fonction[0]].lexem;
        arbre->jeton.valeur.fonction == tabJeton[debut_fonction[0]].fonction;
        debut_fonction[0] = -1;
    }
    // sinon on prend le premier opérateur
    else {
        int i = 0;
        while (is_inPar(debut_parenthese, fin_parenthese, operande[i]) == 0) {
            i++;
        }
        arbre->jeton.lexem == tabJeton[operande[i]].lexem;
        arbre->jeton.valeur.operateur == tabJeton[operande[i]].operateur;
        operande[i] = -1;
    }

    
    tab[0][0][1] = tabJeton[1];
    // sin(x+3)+6
    // sin(x+3)6
    // (x+3)6
    // x
}

void reste(Jeton tabJeton[], Node *arbre) {

}

void print_tree(Node *arbre) {
    
}

Node *syntaxe(Jeton tabJeton[])
{
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
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = DIV_ZERO;
        }

        // test erreur 102 - 103 (parenthèse)
        if (ouvrir > fermer)
            arbre->jeton.valeur.erreur = PAR_NONFERM, arbre->jeton.lexem = ERREUR;
        else if (fermer > ouvrir)
            arbre->jeton.valeur.erreur = PAR_NONOUVER, arbre->jeton.lexem = ERREUR;

        // test erreur 104 (double opérande)
        if (tabJeton[i].operateur == tabJeton[i + 1].operateur)
        {
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = DOUBLE_OPE;
        }

        // test erreur 107 (Barre non fermée pour val abs)
        if (doublon_absolu % 2 != 0)
            arbre->jeton.lexem = ERREUR;
            arbre->jeton.valeur.erreur = BAR_ABS;

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


void test_erreur(Node *arbre, Jeton tab[]) {

    int i;
    size_t length = sizeof(tab)/sizeof(tab[0]);

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

}

int main()
{
    // test tab
    // Jeton tab[5];
    // tab[0].lexem = BARRE;
    // tab[1].lexem = PAR_OUV;
    // tab[2].lexem = REEL;
    // tab[3].lexem = PAR_FERM;
    // tab[4].lexem = BARRE;


    // Node *arbre;
    // size_t length = sizeof(tab)/sizeof(tab[0]);
    // int i;


    // arbre = syntaxe(tab);

    // test_erreur(arbre, tab);

    Node *arbre = -1;
    Node *arbre2 = -1;
    int i = NULL;

    printf("%d     %d", arbre,arbre2);
    

    printf("\n\n\nFin du programme...\n\n");

    return 0;
}