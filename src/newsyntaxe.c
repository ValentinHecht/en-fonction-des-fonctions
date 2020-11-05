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

Node *create_node(Jeton *tabJeton, int elem, int *position) {
    Node *node;

    for (int k = 0; k < elem; k++) {
        printf("%d\n",tabJeton[k].lexem);
    }

    node = malloc(sizeof(*node));

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

    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem-1) {
        node->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        node->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\n\nPOSITION DU JETON: 0");
        *position = 0;
    }
    // sinon on prend le premier opérateur entre les parenthèse
    else if (o != 0 && dp > 1) {
        int i = 0;
        int length = longueur(debut_parenthese);
        int *f;

        f = fourchette_operateur(debut_parenthese, fin_parenthese, length, operande[i]);

        for (int j = *f; j < *(f+1); j++) {
            if(tabJeton[j].lexem 
            == OPERATEUR) {
                node->jeton.lexem = tabJeton[j].lexem;
                node->jeton.valeur.operateur = tabJeton[j].operateur;
                printf("\n\nPOSITION DU JETON: %d", j);
                *position = j;
                break;
            }
        }
    } 
    // pas de parenthèse (ou parenthèse inutile), on prend le premier opérateur
    else if (o != 0) {
        node->jeton.lexem = tabJeton[operande[0]].lexem;
        node->jeton.valeur.operateur = tabJeton[operande[0]].operateur;
        printf("\n\nPOSITION DU JETON: %d", operande[0]);
        *position = operande[0];
    }
    // un réel ou un entier
    else if (o == o) {
        int nbVal = 0;
        Jeton val[5];
        char nombre[6];
        for (int j = 0; j < elem; j++) {
            if (tabJeton[j].lexem == REEL) {
                val[nbVal].lexem = tabJeton[j].lexem;
                gcvt(tabJeton[j].reel, 1, nombre[j]);
                nbVal++;
            } else if (tabJeton[j].lexem == VARIABLE) {
                node->jeton.lexem = tabJeton[j].lexem;
            }
        }
        for (int v = 0; v = nbVal; v++) {
            
        }
    }

    printf("\n\n\n");

    return node;
}

Node *create_tree(Jeton *expression, int elem) {
    Node *arbre;
    Node *nodeActuel;

    arbre = malloc(sizeof(*arbre));

    // tab [couche] [colonne] [tableau de jeton du node concerné]
    Jeton memoire [10][20][elem];

    int position = -1;

    int i = 1;
    while(1) {
        for (int j = 0; j < i; j++) {
            nodeActuel = create_node(expression, elem, &position);

            nodeActuel->colonne = j;
            if (i == 1) {
                nodeActuel->pjetonparent = -1;
                nodeActuel->couche = i-1;
                arbre = nodeActuel;
            } else {
                nodeActuel->couche = nodeActuel->pjetonparent->couche+1;
            }

            //for (int k = 0; k < )

            printf("\ncouche : %d\ncolonne : %d\n", arbre->couche, arbre->colonne);
            printf("\ncode lexem: %d\ncode valeur: %d\n", arbre->jeton.lexem, arbre->jeton.valeur.operateur);
            printf("\nLa position du jeton est a la %d\n", position);
            free(nodeActuel);
        }
        i *= 2;
        break;
    }

    return arbre;
}






void afficher(Jeton *tab, int elem) {
    for (int i = 0; i < elem; i++) {
        printf("%d\n", tab[i].lexem);
    }
}