#include <stdio.h>
#include "newsyntaxe.h"


int main() {
    // sin(x)
    Jeton fonction[4];
    fonction[0].lexem = FONCTION;
    fonction[0].fonction = COS;
    
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


    // sin(x*(x+3)+2)+tan(x+7)
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
    expression[13].fonction = TAN;

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
    Jeton test104[4]; // test OK
    test104[0].lexem = REEL;
    test104[0].reel = 2;

    test104[1].lexem = OPERATEUR;
    test104[1].operateur = PLUS;

    test104[2].lexem = OPERATEUR;
    test104[2].operateur = DIV; 
    
    test104[3].lexem = REEL;
    test104[3].reel = 7;

    // ERREUR 107 
    // Fontion : '|-5';???
    Jeton erreur107[4]; //TEST OK

    erreur107[0].lexem = BARRE;
    erreur107[1].lexem = OPERATEUR;
    erreur107[1].operateur = MOINS;
    erreur107[2].lexem = REEL;
    erreur107[2].reel = 5;
    erreur107[3].lexem = BARRE;
    

    // 4

    // test erreurs 
    size_t length = sizeof(expression)/sizeof(expression[0]);

    //printf("%d", length);

    printf("\n\n");
    Node *arbre;
    //arbre  = create_tree(expression, length);
    arbre  = syntaxe(expression, length);


    //syntaxe(graph, length);
    printf("\n\n");

    printf("\nFin du programme...\n");
    free(arbre);

    return 0;
}