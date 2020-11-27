#include "jeton.h"

int *fourchette_operateur(int debut[], int fin[], int length, int pos);

int operande_in_parentesis(int debut[], int fin[], int length, int pos);

Node *create_node(Jeton lexical[], int elem, int *position);

Node *create_tree_recursive(Jeton *expression, int elem);

Node *aller_a(Node *parent, Jeton *expression, int elem, int num);


