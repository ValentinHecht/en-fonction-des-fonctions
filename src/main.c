/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/

#include <stdio.h>
#include <math.h>

#include "evaluateur.h"
#include "newsyntaxe.h"

#define borne_min -10.0;
#define borne_sup 10.0;

int main(int argc, char const *argv[])
{
    float couples[200][2];
    int tab_compteur = 0;
    Node Node_1;
    
    // sin(x)
    Jeton fonction[4];
    fonction[0].lexem = FONCTION;
    fonction[0].fonction = TAN;
    fonction[1].lexem = PAR_OUV;
    fonction[2].lexem = VARIABLE;
    fonction[3].lexem = PAR_FERM;

    // 4+4
    Jeton operande[3];
    operande[0].lexem = REEL;
    operande[0].reel = 4;
    operande[1].lexem = OPERATEUR;
    operande[1].operateur = PLUS;
    operande[2].lexem = REEL;
    operande[2].reel = 4;
    
    // (4+4)
    Jeton op_par[5];
    op_par[0].lexem = PAR_OUV;
    op_par[1].reel = 4;
    op_par[1].lexem = REEL;
    op_par[2].operateur = PLUS;
    op_par[2].lexem = OPERATEUR;
    op_par[3].reel = 4;
    op_par[3].lexem = REEL;
    op_par[4].lexem = PAR_FERM;

// x*(x+3)+2
    Jeton graph[9];
    graph[0].lexem = VARIABLE;
    graph[1].lexem = OPERATEUR;
    graph[1].operateur = FOIS;
    graph[2].lexem = PAR_OUV;
    graph[3].lexem = VARIABLE;
    graph[4].lexem = OPERATEUR;
    graph[4].operateur = PLUS;
    graph[5].lexem = REEL;
    graph[5].reel = 3;
    graph[6].lexem = PAR_FERM;
    graph[7].lexem = OPERATEUR;
    graph[7].operateur = PLUS;
    graph[8].lexem = REEL;
    graph[8].reel = 2;

    // (x*(x+3)+2)+(x+7)
    Jeton expression2[17];
    expression2[0].lexem = PAR_OUV;
    expression2[1].lexem = VARIABLE;
    expression2[2].lexem = OPERATEUR;
    expression2[2].operateur = FOIS;
    expression2[3].lexem = PAR_OUV;
    expression2[4].lexem = VARIABLE;
    expression2[5].lexem = OPERATEUR;
    expression2[5].operateur = PLUS;
    expression2[6].lexem = REEL;
    expression2[6].reel = 3;
    expression2[7].lexem = PAR_FERM;
    expression2[8].lexem = OPERATEUR;
    expression2[8].operateur = PLUS;
    expression2[9].lexem = REEL;
    expression2[9].reel = 2;
    expression2[10].lexem = PAR_FERM;
    expression2[11].lexem = OPERATEUR;
    expression2[11].operateur = PLUS;
    expression2[12].lexem = PAR_OUV;
    expression2[13].lexem = VARIABLE;
    expression2[14].lexem = OPERATEUR;
    expression2[14].operateur = PLUS;
    expression2[15].lexem = REEL;
    expression2[15].reel = 7;
    expression2[16].lexem = PAR_FERM;


    Jeton expression[19];
    expression[0].lexem = FONCTION;
    expression[0].fonction = SIN;
    expression[1].lexem = PAR_OUV;
    expression[2].lexem = VARIABLE;
    expression[3].lexem = OPERATEUR;
    expression[3].operateur = FOIS;
    expression[4].lexem = PAR_OUV;
    expression[5].lexem = VARIABLE;
    expression[6].lexem = OPERATEUR;
    expression[6].operateur = PLUS;
    expression[7].lexem = REEL;
    expression[7].reel = 3;
    expression[8].lexem = PAR_FERM;
    expression[9].lexem = OPERATEUR;
    expression[9].operateur = PLUS;
    expression[10].lexem = REEL;
    expression[10].reel = 2;
    expression[11].lexem = PAR_FERM;
    expression[12].lexem = OPERATEUR;
    expression[12].operateur = PLUS;
    expression[13].lexem = FONCTION;
    expression[13].fonction = SIN;
    expression[14].lexem = PAR_OUV;
    expression[15].lexem = VARIABLE;
    expression[16].lexem = OPERATEUR;
    expression[16].operateur = PLUS;
    expression[17].lexem = REEL;
    expression[17].reel = 7;
    expression[18].lexem = PAR_FERM;

    Jeton test109[13]; // TEST OK (x+4)*(x+5)
    test109[0].lexem = PAR_OUV;
    test109[1].lexem = VARIABLE;
    test109[2].lexem = OPERATEUR;
    test109[3].operateur = PLUS;
    test109[4].lexem = REEL;
    test109[4].reel = 4;
    test109[5].lexem = PAR_FERM;
    test109[6].lexem = OPERATEUR;
    test109[6].operateur = FOIS;
    test109[7].lexem = PAR_OUV;
    test109[8].lexem = VARIABLE;
    test109[9].lexem = OPERATEUR;
    test109[10].operateur = PLUS;
    test109[11].lexem = REEL;
    test109[11].reel = 5;
    test109[12].lexem = PAR_FERM;

    
    // div zero : cos(x)/0;
    Jeton test_div_zero[6]; // TEST OK
    test_div_zero[0].lexem = FONCTION;
    test_div_zero[0].fonction = COS;
    test_div_zero[1].lexem = PAR_OUV;
    test_div_zero[2].lexem = VARIABLE;
    test_div_zero[3].lexem = PAR_FERM;
    test_div_zero[4].lexem = OPERATEUR;
    test_div_zero[4].operateur = DIV;
    test_div_zero[5].lexem = REEL;
    test_div_zero[5].reel = 0;
    
        
    
    // 104: double opérande
    Jeton test104[3]; // test OK
    test104[0].lexem = REEL;
    test104[0].reel = 2;
    test104[1].lexem = OPERATEUR;
    test104[1].operateur = PLUS;
    test104[2].lexem = REEL;
    test104[2].reel = 7;

    // ERREUR 107 
    // Fontion : '|-5';???
    Jeton erreur107[2]; //TEST OK
    erreur107[0].lexem = FONCTION;
    erreur107[0].fonction = ABS;
    erreur107[1].lexem = VARIABLE;

    Node *arbre;
    size_t length = sizeof(expression2)/sizeof(expression2[0]);
    printf("\n\n");
    arbre  = syntaxe(expression2, length);
    //syntaxe(graph, length);
    printf("\n\n");
    printf("\nFin partie syntax\n\n");
    printf("\n-------------------------------------------------------------------------------------------------------------------\n\n");
    float i = borne_min;
    float max = borne_sup;
    while(arbre->couche!=0)
    {
        arbre=arbre->pjetonparent;
    }
    //Arbre *test = arbre->pjetonparent;
    if (get_erreur_syntaxe() == 0) // get erre
    {
        for (i; i <= 1; i++)
        {
            couples[tab_compteur][0] = i;                       // Valeurs de x
            couples[tab_compteur][1] = fonc_eval(arbre, i);  // Valeurs de f(x)
            tab_compteur++;
        }
        for (int y = 0; y < tab_compteur; y++)
        {
            printf("Valeur de x    : %f\n", couples[y][0]);
            printf("Valeur de f(x) : %f\n", couples[y][1]);
            printf("\n");
        }
        printf("\nFin partie evalu\n");
    }
    // Dans partie graphique
    if (get_erreur_syntaxe() || get_erreur_evaluateur())
    {
        
    }
    else
    {
        // print graph et UX
    }
    return 0; 
}
