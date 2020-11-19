#include <stdio.h>
#include "newsyntaxe.h"

// Jeton tabJeton[10];
// size_t length = sizeof(tabJeton)/sizeof(tabJeton[0]);

void init_tab(int tab[], int elem)
{
    for (int i = 0; i < elem; i++)
    {
        tab[i] = -1;
    }
}

int longueur(int tab[])
{
    int i = 0;
    while (tab[i] != -1)
    {
        printf("\ni: %d     ->      %d\n", i, tab[i]);
        i++;
    }
    return i;
}

int *fourchette_operateur(int debut[], int fin[], int length, int pos)
{
    // On suppose que debut.length == fin.length
    int ok[length];
    init_tab(ok, length);
    int o = 0;
    printf("\n");
    for (int m = 0; m < length; m++)
    {
        for (int n = length - 1; n >= 0; n--)
        {
            printf("\ndebut: %d\nfin: %d\nok: %d\n", debut[n], fin[m], ok[m]);
            if (m > 0 && ok[m - 1] == debut[n])
            {
                ok[m] = debut[n - 1];
                break;
            }
            else if (fin[m] > debut[n])
            {
                ok[m] = debut[n];
                break;
            }
        }
        printf("\n------------------- ok: %d ----------------", ok[m]);
    }
    printf("\n");

    static int fourchette[2];
    for (int i = 0; i < length; i++)
    {
        if (ok[i] < ok[i + 1])
        {
            fourchette[0] = fin[i];
            fourchette[1] = ok[i + 1];
            break;
        }
    }
    return fourchette;
}

Node *create_node(Jeton *tabJeton, int elem, int *position)
{
    Node *node;

    for (int k = 0; k < elem; k++)
    {
        printf("%d\n", tabJeton[k].lexem);
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
    for (int i = 0; i < elem; i++)
    {
        if (tabJeton[i].lexem == FONCTION)
            debut_fonction[df] = i, df++, printf("\ndebut_fonction:  %d", i);
        if (tabJeton[i].lexem == PAR_OUV)
            debut_parenthese[dp] = i, dp++, printf("\ndebut_par:  %d", i);
        if (tabJeton[i].lexem == PAR_FERM)
            fin_parenthese[fp] = i, fp++, printf("\nfin_par:  %d", i);
        if (tabJeton[i].lexem == PAR_FERM && dp == fp)
            fin_fonction[ff] = i, ff++, printf("\nfin_fonction: %d", i);

        if (tabJeton[i].lexem == OPERATEUR)
            operande[o] = i, o++, printf("\noperande:  %d", i);
        if (tabJeton[i].lexem == REEL)
            reel[r] = i, r++, printf("\nreel:  %d", i);
        if (tabJeton[i].lexem == VARIABLE)
            var[v] = i, v++, printf("\nvar:  %d", i);
    }


    printf("je vais dans un test\n");
    
    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem - 1) {
        printf("je suis dans le test d'une seule fonctions\n");
        node->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        node->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\n\nPOSITION DU JETON: 0 -> Fonction... On refait un tour");
        *position = 0;

        Jeton expression[elem];
        for (int count = 0, i = 2; i < elem-1; i++, count++) {
            expression[count] = tabJeton[i];
        }
        create_node(expression, elem-3, position);
        
    }
    // sinon on prend le premier opérateur entre les parenthèse
    else if (o != 0 && dp > 1) {
        printf("je suis dans le test operateur dans les parentheses\n");
        int i = 0;
        int length = longueur(debut_parenthese);
        int *f;

        f = fourchette_operateur(debut_parenthese, fin_parenthese, length, operande[i]);

        for (int j = *f; j < *(f + 1); j++)
        {
            if (tabJeton[j].lexem == OPERATEUR) {
                node->jeton.lexem = tabJeton[j].lexem;
                node->jeton.valeur.operateur = tabJeton[j].operateur;
                printf("\n\nPOSITION DU JETON: %d", j);
                *position = j;
                break;
            }
        }
    }
    // pas de parenthèse (ou parenthèse inutile), on prend le premier opérateur
    else if (o != 0)
    {
        printf("je suis dans le test parenthese\n");
        node->jeton.lexem = tabJeton[operande[0]].lexem;
        node->jeton.valeur.operateur = tabJeton[operande[0]].operateur;
        printf("\n\nPOSITION DU JETON: %d", operande[0]);
        *position = operande[0];
    }
    // un réel ou un entier
    else if (o == o)
    {
        printf("je suis dans le test reel ou entier\n");
        int nbVal = 0;
        Jeton val[5];
        char nombre[6];
        for (int j = 0; j < elem; j++)
        {
            if (tabJeton[j].lexem == REEL)
            {
                val[nbVal].lexem = tabJeton[j].lexem;
                gcvt(tabJeton[j].reel, 1, nombre[j]);
                nbVal++;
            }
            else if (tabJeton[j].lexem == VARIABLE)
            {
                node->jeton.lexem = tabJeton[j].lexem;
            }
        }
    }

    printf("\n\n\n");

    return node;
}

Node *create_tree_recursive(Jeton *expression, int elem)
{
    Node *arbre;

    arbre = malloc(sizeof(*arbre));

    arbre = aller_a_gauche(NULL, expression, elem);

    printf("\ncouche : %d\ncolonne : %d\n", arbre->couche, arbre->colonne);
    printf("\ncode lexem: %d\ncode valeur: %d\n", arbre->jeton.lexem, arbre->jeton.valeur.operateur);

    return arbre;
}

Node *aller_a_gauche(Node *parent, Jeton *expression, int elem)
{
    printf("Je suis a gauche\n");
    if (parent == NULL || parent->jeton.lexem != REEL || parent->jeton.lexem != VARIABLE) {

        Node *node;
        int position = -1;

        Jeton gauche[elem - 1];
        Jeton droite[elem - 1];

        node = create_node(expression, elem, &position);

        for (int i = 0, j = position + 1; i < position; i++, j++) {
            gauche[i] = expression[i];
            droite[i] = expression[j];
        }

        node->pjetonparent = parent;
        if (parent == NULL) {
            node->colonne = 0;
            node->couche = 0;
        } else {
            node->colonne = parent->colonne * 2;
            node->couche = parent->couche + 1;
        }

        node->pjetonpreced = aller_a_gauche(node, gauche, position);
        node->pjetonsuiv = aller_a_droite(node, droite, elem - position);

        return node;
    } else {
        printf("fin de gauche\n");
        return NULL;
    }
}

Node *aller_a_droite(Node *parent, Jeton *expression, int elem)
{
    printf("Je suis a droite\n");
    if (parent == NULL || parent->jeton.lexem != REEL || parent->jeton.lexem != VARIABLE) {

        Node *node;
        int position = -1;

        Jeton gauche[elem - 1];
        Jeton droite[elem - 1];

        node = create_node(expression, elem, &position);

        for (int i = 0, j = position + 1; i < position; i++, j++) {
            gauche[i] = expression[i];
            droite[i] = expression[j];
        }

        node->pjetonparent = parent;
        if (parent == NULL) {
            node->colonne = 0;
            node->couche = 0;
        } else {
            node->colonne = parent->colonne * 2 + 1;
            node->couche = parent->couche + 1;
        }

        node->pjetonpreced = aller_a_gauche(node, gauche, position);
        node->pjetonsuiv = aller_a_droite(node, droite, elem - position);

        return node;
    } else {
        printf("fin de droite\n");
        return NULL;
    }
}

Node *create_tree(Jeton *expression, int elem)
{
    Node *arbre;
    Node *racine;
    Node *nodeActuel;

    arbre = malloc(sizeof(*arbre));

    // tab [couche] [colonne] [tableau de jeton du node concerné]
    Jeton memoire[10][20][elem];

    // for (int a = 0; a < elem; a++) {
    //     memoire[0][0][a].lexem = expression[a].lexem;
    //     memoire[0][0][a].reel = expression[a].reel;
    //     memoire[0][0][a].fonction = expression[a].fonction;
    //     memoire[0][0][a].operateur = expression[a].operateur;
    //     memoire[0][0][a].erreur = expression[a].erreur;
    // }///

    int position = -1;

    int i = 1;
    while (1)
    {
        // j = couche
        // k = colonne
        for (int j = 0; j < i; j++)
        {
            for (int k = 0; k < 2 ^ j; k++)
            {
                for (int a = 0; a < elem; a++)
                {
                    memoire[j][k][a].lexem = expression[a].lexem;
                    memoire[j][k][a].reel = expression[a].reel;
                    memoire[j][k][a].fonction = expression[a].fonction;
                    memoire[j][k][a].operateur = expression[a].operateur;
                    memoire[j][k][a].erreur = expression[a].erreur;
                }

                nodeActuel = create_node(expression, elem, &position);

                nodeActuel->colonne = j;
                if (i == 1)
                {
                    nodeActuel->pjetonparent = -1;
                    nodeActuel->couche = i - 1;
                    arbre = nodeActuel;
                    racine = nodeActuel;
                }
                else
                {
                    nodeActuel->couche = nodeActuel->pjetonparent->couche + 1;
                    nodeActuel->colonne = k;
                }

                printf("\ncouche : %d\ncolonne : %d\n", arbre->couche, arbre->colonne);
                printf("\ncode lexem: %d\ncode valeur: %d\n", arbre->jeton.lexem, arbre->jeton.valeur.operateur);
                printf("\nLa position du jeton est a la %d\n", position);
                free(nodeActuel);

                for (int n = 0; n < position; n++)
                {
                    memoire[j + 1][k * 2][n].lexem = expression[n].lexem;
                    memoire[j + 1][k * 2][n].reel = expression[n].reel;
                    memoire[j + 1][k * 2][n].fonction = expression[n].fonction;
                    memoire[j + 1][k * 2][n].operateur = expression[n].operateur;
                    memoire[j + 1][k * 2][n].erreur = expression[n].erreur;
                }
                for (int n = position + 1; n < elem; n++)
                {
                    memoire[j + 1][k * 2 + 1][n].lexem = expression[n].lexem;
                    memoire[j + 1][k * 2 + 1][n].reel = expression[n].reel;
                    memoire[j + 1][k * 2 + 1][n].fonction = expression[n].fonction;
                    memoire[j + 1][k * 2 + 1][n].operateur = expression[n].operateur;
                    memoire[j + 1][k * 2 + 1][n].erreur = expression[n].erreur;
                }
            }
        }
        i += 1;
        break;
    }

    return arbre;
}

void afficher(Jeton *tab, int elem)
{
    for (int i = 0; i < elem; i++)
    {
        printf("%d\n", tab[i].lexem);
    }
}