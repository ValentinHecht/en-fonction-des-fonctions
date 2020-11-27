#include <stdio.h>
#include "newsyntaxe.h"

/**
 * Initialise les valeurs d'un tableau à -1
 * 
 * tab: le tableau
 * elem: le nombre d'element du tableau
 **/
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

Node *syntaxe(Jeton tabJeton[], int elem)
{
    typejeton jeton;

    Node *arbre;
    arbre = malloc(sizeof(*arbre));

    int i = 0;


    // erreur 102-103
    typejeton ouverte;
    ouverte.lexem = PAR_OUV;
    int ouvrir = contains(tabJeton, ouverte);
    typejeton ferme;
    ferme.lexem = PAR_FERM;
    int fermer = contains(tabJeton, ferme);
    printf("test 1 : %d\n", fermer);
    printf("test 2 : %d\n", ouvrir);

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

    while (i != elem)
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
            cause[0]="Une parenthèse ')' est manquante.";
            break;
        }            

        else if (fermer > ouvrir) {

            arbre->jeton.valeur.erreur = PAR_NONOUVER;
            erreur = 1;
            cause[0]="Une parenthèse '(' est manquante.";
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


    //appelle de newsyntaxe
    //size_t length = sizeof(tabJeton)/sizeof(tabJeton[0]);
    //printf("%d", length);

    printf("\n\n");
    //arbre  = create_tree(expression, length);
    if(erreur == 0){
        arbre  = create_tree_recursive(tabJeton, elem);
    }
    else{
        printf("%s",cause[0]);
    }

    return arbre;
}

void test_erreur(Node *arbre, Jeton tab[]) {

    int i;
    size_t length = sizeof(tab)/sizeof(tab[0]);


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
}


void init_tab(int tab[], int elem) {
    for (int i = 0; i < elem; i++) {
        tab[i] = -1;
    }
}

Node *create_node(Jeton *tabJeton, int elem, int *position) {
    Node *node;

    printf("\n--------------------------------------\nCreation d'un noeud\n--------------------------------------\n");


    node = malloc(sizeof(*node));

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


    printf("\nelem: %d !", elem);
    // On récupère les positions de tout les jetons
    for (int i = 0; i < elem; i++) {
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
    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem - 1) {
        printf("\nje suis dans le test d'une seule fonction\n");
        node->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        node->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\nPOSITION DU JETON: 0\n"); //-> Fonction... On refait un tour");
        *position = -2;
    }
    // l'opérateur le moins prioritaire
    else if (o != 0) {
        printf("\nje suis dans le test operateur\n");
        for(int i = 0; i < o; i++) {
            if (tabJeton[operande[i]].operateur == PLUS ||
                tabJeton[operande[i]].operateur  == MOINS) {
                // si l'opérande (qui a un PLUS ou un MOINS) n'est pas dans une parenthèse
                if (operande_in_parentesis(debut_parenthese, fin_parenthese, dp, operande[i]) == 1) {
                    *position = operande[i];
                    break;
                }
            }
        }
        // si aucun valeur n'a été trouvé.. 
        if (*position == -1) *position = operande[0];

        node->jeton.lexem = tabJeton[*position ].lexem;
        node->jeton.valeur.operateur = tabJeton[*position].operateur;
        printf("\n\nPOSITION DU JETON: %d", *position );

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
                node->jeton.lexem = tabJeton[j].lexem;
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

Node *aller_a(Node *parent, Jeton *expression, int elem, int num) {

    if (parent == NULL || (parent->jeton.lexem != REEL && parent->jeton.lexem != VARIABLE)) {
        if (num == -1) printf("INITIALISATION !\n\n");
        else if (num == 0) printf("Je vais a GAUCHE\n");
        else printf("Je vais a DROITE\n");
        
        
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
            parent = node;
            node = node->pjetonpreced;
            ///// sin(cos(0)) = 1
        }
            
        for (int i = 0; i < position; i++) {
            gauche[i] = expression[i];
        }
        for (int j = position + 1, count = 0; j < elem; j++, count++) {
            droite[count] = expression[j];
        }

        init_value(parent, node, num);

        node->pjetonpreced = aller_a(node, gauche, position, 0);
        node->pjetonsuiv = aller_a(node, droite, elem - position - 1, 1);

        return node;
    } 
    else {
        if (num == 0) printf("Fin gauche\n");
        else printf("Fin droite\n");
        return NULL;
    }
}
/**
 * Cherche l'operande le moins prioritaire avec une expression comportant des parentheses
 * 
 * debut: tableau comprenant les positions des parentheses ouvrantes dans la fonctions
 * fin: tableau comprenant les positions des parentheses fermantes dans la fonctions
 * length: longueurs des tableaux (on suppose pas qu'il n'y a pas d'erreurs et que les tableaux ont la meme longueurs)
 * pos: position du jeton a tester
 * 
 * return: 0 si l'operande est dans une parenhese, 1 sinon
 **/
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
            if (m > 0 && ok[m - 1] == debut[n]) {
                ok[m] = debut[n - 1];
                break;
            }
            else if (fin[m] > debut[n]) {
                ok[m] = debut[n];
                break;
            }
        }
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

/**
 * Creation d'un noeud
 * 
 * tabJeton: tableau de jeton
 * elem: nombre d'elements dans tabJeton
 * out position: prend la position du jeton correspondant au noeud actuel
 * 
 * return: Noeud actuel
 **/


/**
 * Fonction principale de la création de l'arbre
 * 
 * expression: tableau de jeton que LEXICAL NOUS DONNE
 * elem: nombre d'elements du tebleau de jeton que LEXICAL NOUS DONNE
 * 
 * return: L'arbre
 **/
Node *create_tree_recursive(Jeton *expression, int elem) {
    Node *arbre;

    arbre = malloc(sizeof(*arbre));

    arbre = aller_a(NULL, expression, elem, -1);

    return arbre;
}


/**
 * Traitements des jetons
 * 
 * parent: c'est le parent
 * expression: tableau de jeton a traiter
 * elem: nombre d'element de "expression"
 * num: bifurcation => 0 -> gauche | 1 -> droite
 * 
 * return le noeud actuel avec plus de detail (colonne, couche, etc..)
 **/


/**
 * Initialise les valeurs "colonne" et "couche" dans le node et le lie au parent
 * 
 * parent: c'est le parent du neoud
 * node: noeud a traiter
 * num: bifurcation => 0 -> gauche | 1 -> droite 
 **/

void init_value(Node *parent, Node *node, int num) {
    node->pjetonparent = parent;
        if (parent == NULL) {
            node->colonne = 0;
            node->couche = 0;
        } 
        else {
            if (num == 0 || num == -1) {
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