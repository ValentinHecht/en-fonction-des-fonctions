#include "jeton.h"



/**
 * Fonction regroupant les tests d'erreurs et la création de l'arbre
 * Destiné à être utiliser par la partie évaluateur
 * 
 * @param tabJeton[] : tableau de jeton que LEXICAL NOUS DONNE
 * @param elem : nombre d'elements du tableau de jeton que LEXICAL NOUS DONNE
 * 
 **/
Node *syntaxe(Jeton tabJeton[], int elem);


/**
 * Fonction de détection d'erreurs
 * 
 * @param tabJeton[] : tableau de jeton que LEXICAL NOUS DONNE
 * @param elem : nombre d'elements du tableau de jeton que LEXICAL NOUS DONNE
 * 
 **/
void errors_detection(Jeton tabJeton[], int elem);


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
 * @return : le noeud actuel avec plus de detail (colonne, couche, etc..)
 **/
Node *aller_a(Node *parent, Jeton *expression, int elem, int num);


/**
 * Creation d'un noeud
 * 
 * @param lexical[] : tableau de jetons
 * @param elem : nombre d'éléments dans tabJeton
 * @param position : prend la position du jeton correspondant au noeud actuel
 * 
 * @return : Noeud actuel
 * 
 **/
Node *create_node(Jeton lexical[], int elem, int *position);


/**
 * Initialise les valeurs "colonne" et "couche" dans le node et le lie au parent
 * 
 * @param parent : c'est le parent du noeud
 * @param node : noeud à traiter
 * @param num : bifurcation. si 0, on descend vers la gauche sinon vers la droite
 **/
void init_value(Node *parent, Node *node, int num);









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
 * Cherche l'operande le moins prioritaire avec une expression comportant des parentheses
 * 
 * @param tab: tableau comprenant les jetons
 * @param jeton: correspond à chaque jeton
 * @param elem: nombre d'elements du tableau de jeton
 * 
 * @return: un integer
 **/
int contains(Jeton tab[], typejeton jeton, int elem);