#include "jeton.h"

int *fourchette_operateur(int debut[], int fin[], int length, int pos);

int operande_in_parentesis(int debut[], int fin[], int length, int pos);

Node *create_node(Jeton lexical[], int elem, int *position);

Node *create_tree_recursive(Jeton *expression, int elem);

Node *aller_a(Node *parent, Jeton *expression, int elem, int num);

int contains(Jeton tab[], typejeton jeton);

void create_tree(Jeton tabJeton[]);

int is_inPar(int debut[], int fin[], int pos);

void test_erreur(Node *arbre, Jeton tab[]);

Node *syntaxe(Jeton tabJeton[], int elem);