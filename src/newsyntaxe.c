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
    // "ok" stock la position de la parenthèse ouvrante en fonction de celui qui la ferme
    // les positions de "ok" sont donc définie en fonction de "fin"
    int ok[length];
    init_tab(ok, length);
    int o = 0;

    for (int m = 0; m < length; m++) {
        for (int n = length - 1; n >= 0; n--) {
            printf("\ndebut: %d\nfin: %d\nok: %d\n", debut[n], fin[m], ok[m]);
            if (m > 0 && ok[m - 1] == debut[n]) {
                ok[m] = debut[n - 1];
                break;
            }
            else if (fin[m] > debut[n]) {
                ok[m] = debut[n];
                break;
            }
        }
        printf("\n------------------- ok: %d ----------------", ok[m]);
    }
    printf("\n");

    int fourchette[2];
    int res = 1;
    for (int i = 0; i < length; i++) {
        if (ok[i] < pos && pos < fin[i]) {
            res = 0;
            break;
        }
    }
    return res;
}

int operande_in_parentesis(int debut[], int fin[], int length, int pos) {
    if (length == 0) return 1;

    // test des faux positifs (parenthèses inutiles): (4*3+8)
    if (debut[0] == 0 && fin[0] == length-1 && length == 1) return 1;

    // "ok" stock la position de la parenthèse ouvrante en fonction de celui qui la ferme
    // les positions de "ok" sont donc définie en fonction de "fin"
    int ok[length];
    init_tab(ok, length);

    for (int m = 0; m < length; m++) {
        for (int n = length - 1; n >= 0; n--) {
            //printf("\ndebut: %d\nfin: %d\nok: %d\n", debut[n], fin[m], ok[m]);
            if (m > 0 && ok[m - 1] == debut[n]) {
                ok[m] = debut[n - 1];
                break;
            }
            else if (fin[m] > debut[n]) {
                ok[m] = debut[n];
                break;
            }
        }
        //printf("\n------------------- ok: %d ----------------", ok[m]);
    }
    printf("\n");

    int res = 1;
    for (int i = 0; i < length; i++) {
        if (ok[i] < pos && pos < fin[i]) {
            res = 0;
            break;
        }
    }
    return res;
}

Node *create_node(Jeton *tabJeton, int elem, int *position) {
    Node *node;

    printf("\n--------------------------------------\nCreation d'un noeud\n--------------------------------------\n");

    /*
    for (int k = 0; k < elem; k++)
    {
        printf("%d\n", tabJeton[k].lexem);
    }
    */

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
        if (tabJeton[i].lexem == PAR_FERM && dp == fp && df != 0)
            fin_fonction[ff] = i, ff++, printf("\nfin_fonction: %d", i);

        if (tabJeton[i].lexem == OPERATEUR)
            operande[o] = i, o++, printf("\noperande:  %d", i);
        if (tabJeton[i].lexem == REEL)
            reel[r] = i, r++, printf("\nreel:  %d", i);
        if (tabJeton[i].lexem == VARIABLE)
            var[v] = i, v++, printf("\nvar:  %d", i);
    }


    //printf("\nje vais dans un test\n");
    
    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem - 1) {
        printf("\nje suis dans le test d'une seule fonctions\n");
        node->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        node->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\nPOSITION DU JETON: 0\n"); //-> Fonction... On refait un tour");
        *position = -2;

        /*
        Jeton expression[elem];
        for (int count = 0, i = 2; i < elem-1; i++, count++) {
            expression[count] = tabJeton[i];
        }
        create_node(expression, elem-3, position);
        *position += 2;
        */
    }
    /*
    // sinon on prend le premier opérateur entre les parenthèse
    else if (o != 0 && dp > 0) {
        printf("je suis dans le test operateur dans les parentheses\n");
        int i = 0;
        int length = longueur(debut_parenthese);
        int *f;

        
        f = fourchette_operateur(debut_parenthese, fin_parenthese, length, operande[i]);

        for (int j = *f; j < *(f + 1); j++) {
            if (tabJeton[j].lexem == OPERATEUR) {
                node->jeton.lexem = tabJeton[j].lexem;
                node->jeton.valeur.operateur = tabJeton[j].operateur;
                printf("\n\nPOSITION DU JETON: %d", j);
                *position = j;
                break;
            }
        }
        
    }
    */
    // l'opérateur le moins prioritaire
    else if (o != 0) {
        printf("\nje suis dans le test operateur\n");
        for(int i = 0; i < o; i++) {
            if (tabJeton[operande[i]].operateur == PLUS ||
                tabJeton[operande[i]].operateur  == MOINS) {
                // si l'opérande (qui un PLUS ou un MOINS) n'est pas dans une parenthèse
                if (operande_in_parentesis(debut_parenthese, fin_parenthese, dp, operande[i]) == 1) {
                    *position = operande[i];
                    //printf("\ntest: %d\n",operande_in_parentesis(debut_parenthese, fin_parenthese, dp, operande[i]));
                    break;
                }
            }
        }

        // si aucune valeure n'a été trouvé.. 
        if (*position == -1) *position = operande[0];

        node->jeton.lexem = tabJeton[*position ].lexem;
        node->jeton.valeur.operateur = tabJeton[*position].operateur;
        printf("\n\nPOSITION DU JETON: %d", *position );
        //*position = operande[0];
    }
    // un réel ou un entier
    else if (o == 0) {
        printf("\nje suis dans le test reel ou entier\n");
        int nbVal = 0;
        Jeton val[5];
        char nombre[6];
        for (int j = 0; j < elem; j++) {
            if (tabJeton[j].lexem == REEL) {
                printf("\nreel\n");
                //val[nbVal].lexem = tabJeton[j].lexem;
                node->jeton.lexem = tabJeton[j].lexem;
                //gcvt(tabJeton[j].reel, 1, nombre[j]);
                //nbVal++;
            }
            else if (tabJeton[j].lexem == VARIABLE) {
                printf("\nvariable\n");
                node->jeton.lexem = tabJeton[j].lexem;
            }
        }
        *position = -1;
    }

    printf("\n\n\n");

    return node;
}

// enlever les fonctions
Jeton *enlever(Jeton *expression, int elem) {
    //if (expression[0].lexem == )

    return expression;
}

Node *create_tree_recursive(Jeton *expression, int elem) {
    Node *arbre;

    arbre = malloc(sizeof(*arbre));

    arbre = aller_a(NULL, expression, elem, 0);

    //printf("\ncouche : %d\ncolonne : %d\n", arbre->couche, arbre->colonne);
    //printf("\ncode lexem: %d\ncode valeur: %d\n", arbre->jeton.lexem, arbre->jeton.valeur.operateur);

    return arbre;
}

// num = 0 : aller à gauche
// num = 1 : aller à droite
Node *aller_a(Node *parent, Jeton *expression, int elem, int num) {

    if (parent == NULL || (parent->jeton.lexem != REEL && parent->jeton.lexem != VARIABLE)) {
        if (num == 0) printf("Je vais a GAUCHE\n");
        else printf("Je vais a DROITE\n");
        
        //if(parent != NULL)
        //printf("\njeton du parent : %d \n", parent->jeton.lexem);
        
        Node *node;
        int position = -1;

        Jeton gauche[elem - 1];
        Jeton droite[elem - 1];

        node = create_node(expression, elem, &position);  

        // ou faire un while
        while (position == -2) {
            // enlever 3 termes dans expressions
            for(int i = 0; i < elem-3; i++) {
                expression[i] = expression[i+2];
            }
            elem -= 3;
            
            // placer le jeton de la fonction et descendre d'un cran
            init_value(parent, node, num);

            // je refais un creat node
            node->pjetonpreced = create_node(expression, elem, &position);
            node = node->pjetonpreced;

            ///// sin(cos(0)) = 1
        } //else {
            
        for (int i = 0; i < position; i++) {
            gauche[i] = expression[i];
            //printf("\nnum: %d\n", gauche[i]);
        }
        for (int j = position + 1, count = 0; j < elem; j++, count++) {
            droite[count] = expression[j];
        }
        //}

        init_value(parent, node, num);

        node->pjetonpreced = aller_a(node, gauche, position, 0);
        node->pjetonsuiv = aller_a(node, droite, elem - position, 1);

        return node;
    } else {
        if (num == 0) printf("Fin gauche\n");
        else printf("Fin droite\n");
        return NULL;
    }
}

void init_value(Node *parent, Node *node, int num) {
    node->pjetonparent = parent;
        if (parent == NULL) {
            node->colonne = 0;
            node->couche = 0;
           
        } else {
            if (num == 0) {
                node->colonne = parent->colonne * 2;
                node->couche = parent->couche + 1;
            } else {
                node->colonne = parent->colonne * 2 + 1;
                node->couche = parent->couche + 1;
            }
        }
    printf("\nJe suis dans la couche: %d\nJe suis dans la colonne: %d\n", node->couche, node->colonne);
    printf("J'ai la valeur: %d\n\n", node->jeton.lexem);   
}

/*
Node *aller_a_droite(Node *parent, Jeton *expression, int elem) {
    printf("Je suis a droite\n");
    if (parent == NULL || parent->jeton.lexem != REEL || parent->jeton.lexem != VARIABLE) {

        Node *node;
        int position = -1;

        Jeton gauche[elem - 1];
        Jeton droite[elem - 1];
    sin
    / 
    +   
  x    3
        node = create_node(expression, elem, &position);

        for (int i = 0; i < position; i++) {
            gauche[i] = expression[i];
        }
        for (int j = position + 1, count = 0; j < elem; j++, count++) {
            droite[count] = expression[j];
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
*/

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
    // }

    int position = -1;

    int i = 1;
    while (1)
    {
        // j = couche
        // k = colonne
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < 2 ^ j; k++) {
                for (int a = 0; a < elem; a++) {
                    memoire[j][k][a].lexem = expression[a].lexem;
                    memoire[j][k][a].reel = expression[a].reel;
                    memoire[j][k][a].fonction = expression[a].fonction;
                    memoire[j][k][a].operateur = expression[a].operateur;
                    memoire[j][k][a].erreur = expression[a].erreur;
                }

                nodeActuel = create_node(expression, elem, &position);

                nodeActuel->colonne = j;
                if (i == 1) {
                    nodeActuel->pjetonparent = -1;
                    nodeActuel->couche = i - 1;
                    arbre = nodeActuel;
                    racine = nodeActuel;
                }
                else {
                    nodeActuel->couche = nodeActuel->pjetonparent->couche + 1;
                    nodeActuel->colonne = k;
                }

                printf("\ncouche : %d\ncolonne : %d\n", arbre->couche, arbre->colonne);
                printf("\ncode lexem: %d\ncode valeur: %d\n", arbre->jeton.lexem, arbre->jeton.valeur.operateur);
                printf("\nLa position du jeton est a la %d\n", position);
                free(nodeActuel);

                for (int n = 0; n < position; n++) {
                    memoire[j + 1][k * 2][n].lexem = expression[n].lexem;
                    memoire[j + 1][k * 2][n].reel = expression[n].reel;
                    memoire[j + 1][k * 2][n].fonction = expression[n].fonction;
                    memoire[j + 1][k * 2][n].operateur = expression[n].operateur;
                    memoire[j + 1][k * 2][n].erreur = expression[n].erreur;
                }
                for (int n = position + 1; n < elem; n++) {
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