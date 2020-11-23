/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
/**
 * Fonction récursive permettant l'évaluation d'une fonction
 * @param *A : Adresse de l'arbre à évaluer
 * @param x : valeur de la variable x pour la fonction
 * @return : renvoie un tableau de valeur correspondant au couple (abscisse,ordonnée) de la borne inférieur à la borne supérieure
*/
float fonc_eval(Noeud *A, float x);