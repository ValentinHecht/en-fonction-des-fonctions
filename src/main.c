/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include <stdio.h>
#include <math.h>

#include "evaluateur.h"
#include "newsyntaxe.h"
#include "lexical.h"

int main(int argc, char const *argv[])
{
    float couples[200][2];
    int tab_compteur = 0;
    Node Node_1;
    char operation[30];

    
    printf("Entrez votre fonction : ");
    scanf("%s", operation);
    printf("Entrez votre premiere borne : ");
    scanf("%lf", &borneStart);
    printf("Entrez votre deuxieme borne : ");
    scanf("%lf", &borneEnd);

    //Partie graphique entrée fonc





    //Partie lexicale
    Jeton* jetons_lexi = analyse_lexical(operation);

    // Partie syntaxe
    Node *arbre;
    printf("\n\n");
    arbre  = syntaxe(jetons_lexi, get_length_tableau()-1);
    printf("\nFin partie syntax\n\n");
    float i = borneStart;
    float max = borneEnd;
    while(arbre->couche!=0)
    {
        arbre=arbre->pjetonparent;
    }
    
    // Partie Evaluateur
    if (get_erreur_syntaxe() == 0) // get erre
    {
        for (i; i <= max; i++)
        {
            couples[tab_compteur][0] = i;                    // Valeurs de x
            couples[tab_compteur][1] = fonc_eval(arbre, i);  // Valeurs de f(x)
            tab_compteur++;
        }
        for (int y = 0; y < tab_compteur; y++)
        {
            printf("Valeur de x    : %f\n", couples[y][0]);
            printf("Valeur de f(x) : %f\n", couples[y][1]);
            printf("\n");
        }
        printf("\nTaille du tableau : %d\n\n", get_length_tableau()-1);
        printf("\nFin partie evalu\n");
    }

    // Dans partie graphique
    if (get_erreur_syntaxe() || get_erreur_evaluateur())
    {
        
    }
    else
    {
        // Partie graphe affichage
    }

    return 0; 
}
