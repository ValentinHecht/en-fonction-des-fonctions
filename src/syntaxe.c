#include <stdio.h>
#include "jeton.h"


Node *syntaxe (typejeton tabJeton[], int position) {

    // sin(x+2)
    // sin(x++3))
    // doiqsnd(x+3)

    // fonction, variable, opérande, réel

    typejeton jeton;

    Node *arbre = NULL;

    int i = 0;
    size_t length = sizeof(tabJeton);

    while (i != length) {
        switch (jeton.erreur)
        {
        case tabJeton[i].jeton :
            
            break;
        
        default:
            break;
        }
    }
    
    return arbre;
}