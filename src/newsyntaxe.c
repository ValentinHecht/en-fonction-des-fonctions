#include <stdio.h>
#include "newsyntaxe.h"

int erreur_syntax = 0;
char *cause[];

int get_erreur_syntaxe()
{
    return erreur_syntax;
}
char get_cause_syntaxe()
{
    return &cause[0];
}



void init_value(Node *parent, Node *Node, int num)
{
    Node->pjetonparent = parent;
    if (parent == NULL)
    {
        Node->colonne = 0;
        Node->couche = 0;
    }
    else
    {
        if (num == 0 || num == -1)
        {
            Node->colonne = parent->colonne * 2;
            Node->couche = parent->couche + 1;
        }
        else
        {
            Node->colonne = parent->colonne * 2 + 1;
            Node->couche = parent->couche + 1;
        }
    }
    printf("\nJe suis dans la couche: %d\nJe suis dans la colonne: %d\n", Node->couche, Node->colonne);
    printf("J'ai la valeur: %d\n\n", Node->jeton.lexem);
}

Node *aller_a(Node *parent, Jeton *expression, int elem, int num)
{
    if (parent == NULL || (parent->jeton.lexem != REEL && parent->jeton.lexem != VARIABLE))
    {
        if (num == -1)
            printf("INITIALISATION !\n\n");
        else if (num == 0)
            printf("Je vais a GAUCHE\n");
        else
            printf("Je vais a DROITE\n");
        Node *Node;
        int position = -1;
        Jeton gauche[elem - 1];
        Jeton droite[elem - 1];
        Node = create_Node(expression, elem, &position);
        // ou faire un while
        while (position == -2)
        {
            // enlever 3 termes dans expressions
            for (int i = 0; i < elem - 3; i++)
            {
                expression[i] = expression[i + 2];
            }
            elem -= 3;
            // placer le jeton de la fonction et descendre d'un cran
            init_value(parent, Node, num);
            // je refais un creat Node
            Node->pjetonpreced = create_Node(expression, elem, &position);
            parent = Node;
            Node = Node->pjetonpreced;
        }

        for (int i = 0; i < position; i++)
        {
            gauche[i] = expression[i];
        }
        for (int j = position + 1, count = 0; j < elem; j++, count++)
        {
            droite[count] = expression[j];
        }
        init_value(parent, Node, num);
        Node->pjetonpreced = aller_a(Node, gauche, position, 0);
        Node->pjetonsuiv = aller_a(Node, droite, elem - position - 1, 1);
        return Node;
    }
    else
    {
        if (num == 0)
            printf("Fin gauche\n");
        else
            printf("Fin droite\n");
        return NULL;
    }
}

Node *create_tree_recursive(Jeton *expression, int elem)
{
    Node *arbre;
    arbre = malloc(sizeof(*arbre));
    arbre = aller_a(NULL, expression, elem, -1);
    return arbre;
}

Node *syntaxe(Jeton tabJeton[], int elem)
{
    typejeton jeton;
    Node *arbre;
    arbre = malloc(sizeof(*arbre));

    test_erreur(tabJeton, elem, arbre);
    
    printf("\n\n");
    //arbre  = create_tree(expression, length);
    if (erreur_syntax == 0)
    {
        arbre = create_tree_recursive(tabJeton, elem);
    }
    else
    {
        printf("%s", cause[0]);
    }
    return arbre;
}

int contains(Jeton tab[], typejeton jeton, int elem)
{
    int occ = 0;
    for (int i = 0; i < elem; i++)
    {
        if (tab[i].lexem == jeton.lexem)
        {
            occ++;
        }
    }
    return occ;
}

int is_inPar(int debut[], int fin[], int pos)
{
    // On suppose que debut.length == fin.length
    size_t length = sizeof(debut) / sizeof(debut[0]);
    for (int i = 0; i < length; i++)
    {
        // c'est dans la parenthese/fonction
        if (debut[i] < pos && pos < fin[i])
        {
            return 0;
        }
    }
    return 1;
}




void init_tab(int tab[], int elem)
{
    for (int i = 0; i < elem; i++)
    {
        tab[i] = -1;
    }
}

Node *create_Node(Jeton *tabJeton, int elem, int *position)
{
    Node *Node;
    printf("\n--------------------------------------\nCreation d'un Node\n--------------------------------------\n");
    Node = malloc(sizeof(*Node));
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
    // si l'expression ne contient qu'une fonction..
    if (debut_fonction[0] == 0 && fin_fonction[0] == elem - 1)
    {
        printf("\nje suis dans le test d'une seule fonction\n");
        Node->jeton.lexem = tabJeton[debut_fonction[0]].lexem;
        Node->jeton.valeur.fonction = tabJeton[debut_fonction[0]].fonction;
        printf("\nPOSITION DU JETON: 0\n"); //-> Fonction... On refait un tour");
        *position = -2;
    }
    // l'opérateur le moins prioritaire
    else if (o != 0)
    {
        printf("\nje suis dans le test operateur\n");
        for (int i = 0; i < o; i++)
        {
            if (tabJeton[operande[i]].operateur == PLUS ||
                tabJeton[operande[i]].operateur == MOINS)
            {
                // si l'opérande (qui a un PLUS ou un MOINS) n'est pas dans une parenthèse
                if (operande_in_parentesis(debut_parenthese, fin_parenthese, dp, operande[i]) == 1)
                {
                    *position = operande[i];
                    break;
                }
            }
        }
        // si aucun valeur n'a été trouvé..
        if (*position == -1)
            *position = operande[0];
        Node->jeton.lexem = tabJeton[*position].lexem;
        Node->jeton.valeur.operateur = tabJeton[*position].operateur;
        printf("\n\nPOSITION DU JETON: %d", *position);
    }
    // un réel ou un entier
    else if (o == 0)
    {
        printf("\nje suis dans le test reel ou entier\n");
        int nbVal = 0;
        Jeton val[5];
        char nombre[6];
        for (int j = 0; j < elem; j++)
        {
            if (tabJeton[j].lexem == REEL)
            {
                printf("\nreel\n");
                Node->jeton.lexem = tabJeton[j].lexem;
                Node->jeton.valeur.reel = tabJeton[j].reel;
                printf("\nval: %f", Node->jeton.valeur.reel);
            }
            else if (tabJeton[j].lexem == VARIABLE)
            {
                printf("\nvariable\n");
                Node->jeton.lexem = tabJeton[j].lexem;
            }
        }
        *position = -1;
    }
    printf("\n\n\n");
    return Node;
}

int operande_in_parentesis(int debut[], int fin[], int length, int pos)
{
    if (length == 0)
        return 1;
    // test des faux positifs (parenthèses inutiles): (4*3+8)
    if (debut[0] == 0 && fin[0] == length - 1 && length == 1)
        return 1;
    // "ok" stock la position de la parenthèse ouvrante en fonction de celui qui la ferme
    // les positions de "ok" sont donc définie en fonction de "fin"
    int ok[length];
    init_tab(ok, length);
    for (int m = 0; m < length; m++)
    {
        for (int n = length - 1; n >= 0; n--)
        {
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
    }
    printf("\n");
    int res = 1;
    for (int i = 0; i < length; i++)
    {
        if (ok[i] < pos && pos < fin[i])
        {
            res = 0;
            break;
        }
    }
    return res;
}