#ifndef JETON
#define JETON
#include "jeton.h"

int *fourchette_operateur(int debut[], int fin[], int length, int pos);

/**
 * Cherche l'operande le moins prioritaire avec une expression comportant des parentheses
 * 
 * @param debut: tableau comprenant les positions des parentheses ouvrantes dans la fonctions
 * @param fin: tableau comprenant les positions des parentheses fermantes dans la fonctions
 * @param length: longueurs des tableaux (on suppose pas qu'il n'y a pas d'erreurs et que les tableaux ont la meme longueurs)
 * @param pos: position du jeton a tester
 * 
 * @return: 0 si l'operande est dans une parenhese, 1 sinon
 **/
int operande_in_parentesis(int debut[], int fin[], int length, int pos);

/**
 * Creation d'un Node
 * 
 * @param lexical[] : tableau de jetons
 * @param elem : nombre d'éléments dans tabJeton
 * @param position : prend la position du jeton correspondant au Node actuel
 * 
 * @return : Node actuel
 * 
 **/
Node *create_Node(Jeton lexical[], int elem, int *position);

/**
 * Fonction principale de la création de l'arbre
 * 
 * @param expression : tableau de jeton que LEXICAL NOUS DONNE
 * @param elem : nombre d'elements du tableau de jeton que LEXICAL NOUS DONNE
 * 
 * @return : retourne l'arbre créé
 * 
 **/
Node *create_tree_recursive(Jeton *expression, int elem);

/**
 * Traitements des jetons
 * 
 * @param parent : c'est le parent
 * @param expression : tableau de jeton à traiter
 * @param elem : nombre d'éléments de "expression"
 * @param num : bifurcation. si 0, on descend vers la gauche sinon vers la droite
 * 
 * @return : le Node actuel avec plus de detail (colonne, couche, etc..)
 **/
Node *aller_a(Node *parent, Jeton *expression, int elem, int num);

int contains(Jeton tab[], typejeton jeton, int elem);

void create_tree(Jeton tabJeton[]);

int is_inPar(int debut[], int fin[], int pos);

void test_erreur(Jeton tabJeton[], int elem, Node *arbre);

Node *syntaxe(Jeton tabJeton[], int elem);

int get_erreur_syntaxe();

char get_cause_syntaxe();

#endif