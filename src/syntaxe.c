#include <stdio.h>
#include "jeton.h"


Node *syntaxe (Jeton tabJeton[], int position) {

    // sin(x+2)
    // sin(x++3))
    // doiqsnd(x+3)

    // fonction, variable, opérande, réel

    typejeton jeton;

    Node *arbre = NULL;

    int i = 0;
    size_t length = sizeof(tabJeton);

    while (i != length) {
        switch (tabJeton[i])
        {
        case tabJeton[i].jeton :
            
            break;
        
        default:
            break;
        }
    }
    
    return arbre;
}

int contains (Jeton tab[], typejeton jeton) {
    int occ = 0;

    for (int i = 0; i < sizeof(tab); i++) {
        if (tab[i].lexem == jeton.lexem) {
            occ++;
        } else if (tab[i].operateur == jeton.valeur.operateur) {
            occ++;
        }
    } 
    
    return occ;
}

// précédent : 
// suivant : 

// Retourner le jeton d'erreur