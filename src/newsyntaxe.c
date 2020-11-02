#include <stdio.h>
#include "newsyntaxe.h"

// Jeton tabJeton[10];
// size_t length = sizeof(tabJeton)/sizeof(tabJeton[0]);

void init_tab(int tab[], int elem) {
    for (int i = 0; i < elem; i++) {
        tab[i] = -1;
    }
}

int longueur(int tab[]) {
    int i = 0;
    while (tab[i] != -1) {
        printf("\ni: %d     ->      %d\n", i, tab[i]);
        i++;
    }
    return i;
}


int *fourchette_operateur(int debut[], int fin[], int length, int pos) {
    // On suppose que debut.length == fin.length

    int ok[length];
    init_tab(ok, length);
    int o = 0;
    printf("\n");
    for (int m = 0; m < length; m++) {
        for (int n = length-1; n >= 0; n--) {
            printf("\ndebut: %d\nfin: %d\nok: %d\n", debut[n], fin[m], ok[m]);
            if (m > 0 && ok[m-1] == debut[n]) {
                ok[m] = debut[n-1];
                break;
            } else if (fin[m] > debut[n]) {
                ok[m] = debut[n];
                break;
            } 
        }
        printf("\n------------------- ok: %d ----------------", ok[m]);
    }
    printf("\n");

    static int fourchette[2];
    for (int i = 0; i < length; i++) {
        if (ok[i] < ok[i+1]) {
            fourchette[0] = fin[i]; 
            fourchette[1] = ok[i+1];
            break;
        }
    }

    return fourchette;
}

Node *create_tree(Jeton *tabJeton, int elem) {
    Node *arbre;
    Node *nodeActuel; 

    for (int k = 0; k < elem; k++) {
        printf("%d\n",tabJeton[k].lexem);
    }

    arbre = malloc(sizeof(*arbre));

    // tab [couche] [colonne] [tableau de jeton du node concerné]
    //Jeton tab [10][20][length];

    // déclaration de tableau contenant les indices de différents jetons dans "tabJeton"
    int debut_fonction[5];
    int fin_fonction[5];
    init_tab(debut_fonction, 5);
    init_tab(fin_fonction, 5);
    int df = 0;
    int ff = 0;

    int debut_parenthese[10];
    int fin_parenthese[10];
    init_tab(debut_parenthese, 10);
    init_tab(fin_parenthese, 10);
    int dp = 0;
    int fp = 0;

    int operande[20];
    init_tab(operande, 20);
    int o = 0;

    int reel[40];
    init_tab(reel, 40);
    int r = 0;

    int var[20];
    init_tab(var, 20);
    int v = 0;

    // On récupère les positions de tout les jetons
    for (int i = 0; i < elem; i++) {
        if (tabJeton[i].lexem == FONCTION) debut_fonction[df] = i, df++, printf("\ndebut_fonction:  %d", i);
        if (tabJeton[i].lexem == PAR_OUV) debut_parenthese[dp] = i, dp++, printf("\ndebut_par:  %d", i);
        if (tabJeton[i].lexem == PAR_FERM) fin_parenthese[fp] = i, fp++, printf("\nfin_par:  %d", i);
        if (tabJeton[i].lexem == PAR_FERM && dp == fp) fin_fonction[ff] = i, ff++, printf("\nfin_fonction: %d", i);

        if (tabJeton[i].lexem == OPERATEUR) operande[v] = i, o++, printf("\noperande:  %d", i);
        if (tabJeton[i].lexem == REEL) reel[v] = i, r++, printf("\nreel:  %d", i);
        if (tabJeton[i].lexem == VARIABLE) var[v] = i, v++, printf("\nvar:  %d", i);
        //tab[0][0][i] = tabJeton[i];
    }

    // On crée le premier node de l'arbre
    arbre->couche = 0;
    arbre->colonne = 0;
    arbre->pjetonparent = -1;

    int marque_page;
    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem-1) {
        arbre->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        arbre->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\n\nPOSITION DU JETON: 0");
        marque_page = 0;
        debut_fonction[0] = -1;
    }
    // sinon on prend le premier opérateur entre les parenthèse
    else if (o != 0 && dp > 1) {
        int i = 0;
        int length = longueur(debut_parenthese);
        int *f;

        f = fourchette_operateur(debut_parenthese, fin_parenthese, length, operande[i]);

        for (int j = *f; j < *(f+1); j++) {
            if(tabJeton[j].lexem == OPERATEUR) {
                arbre->jeton.lexem = tabJeton[j].lexem;
                arbre->jeton.valeur.operateur = tabJeton[j].operateur;
                printf("\n\nPOSITION DU JETON: %d", j);
                marque_page = j;
                break;
            }
        }
    } 
    // pas de parenthèse (ou parenthèse inutile), on prend le premier opérateur
    else if (o != 0) {
        arbre->jeton.lexem = tabJeton[operande[0]].lexem;
        arbre->jeton.valeur.operateur = tabJeton[operande[0]].operateur;
        printf("\n\nPOSITION DU JETON: %d", operande[0]);
        marque_page = operande[0];
    }

    return arbre;
}



void afficher(Jeton *tab, int elem) {
    for (int i = 0; i < elem; i++) {
        printf("%d\n", tab[i].lexem);
    }
}