/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#ifndef JETON
#define JETON
#include "jeton.h"

/**
 * Fonction récursive permettant l'évaluation d'une fonction
 * 
 * @param A : Arbre à évaluer
 * @param x : valeur de la variable x pour la fonction
 * 
 * @return : renvoie un tableau de valeur correspondant au couple (abscisse,ordonnée) de la borne inférieur à la borne supérieure
*/
float fonc_eval(Arbre A, float x);

int get_erreur_evaluateur();

char get_cause_evaluateur();

#endif