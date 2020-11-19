#include "jeton.h"

int *fourchette_operateur(int debut[], int fin[], int length, int pos);

Node *create_node(Jeton lexical[], int elem, int *position);

Node *create_tree(Jeton *tabJeton, int elem);

void afficher(Jeton *tab, int elem);

Node *create_tree_recursive(Jeton *expression, int elem);

Node *aller_a_gauche(Node *parent, Jeton *expression, int elem);

Node *aller_a_droite(Node *parent, Jeton *expression, int elem);