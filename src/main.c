#include <stdio.h>
#include "newsyntaxe.h"

int main() {
    // sin(x)
    Jeton fonction[4];
    fonction[0].fonction = COS;
    fonction[0].lexem = FONCTION;
    fonction[1].lexem = PAR_OUV;
    fonction[2].lexem = VARIABLE;
    fonction[3].lexem = PAR_FERM;

    // 4+4
    Jeton operande[3];
    operande[0].reel = 4;
    operande[0].lexem = REEL;
    operande[1].operateur = PLUS;
    operande[1].lexem = OPERATEUR;
    operande[2].reel = 4;
    operande[2].lexem = REEL;

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

    // 4
    
    size_t length = sizeof(graph)/sizeof(graph[0]);

    printf("%d", length);

    printf("\n\n");
    Node *arbre;
    //arbre  = create_tree(expression, length);
    arbre  = create_tree_recursive(graph, length);
    printf("\n\n");

    printf("\nFin du programme...\n");

    return 0;
}