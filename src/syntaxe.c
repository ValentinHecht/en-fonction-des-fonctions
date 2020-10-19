#include <stdio.h>
#include "jeton.h"


Node *syntaxe (Jeton tabJeton[]) {

    // sin(x+2)
    // sin(x++3))
    // doiqsnd(x+3)

    // fonction, variable, opérande, réel

    typejeton jeton;

    Node arbre[sizeof(tabJeton)];

    int i = 0;
    size_t length = sizeof(tabJeton);

    while (i != length) {

        // Au début de la boucle, ajoute dans l'arbre le suivant




        // test erreur 100 (division par 0)
        if (tabJeton[i].operateur == DIV 
        && arbre[i].pjetonsuiv->jeton.valeur.reel == 0) {
            arbre[i].jeton.valeur.erreur = DIV_ZERO;
        }


        // test erreur 102 - 103 (parenthèse)
        typejeton ouverte; 
        ouverte.lexem=PAR_OUV;
        int ouvrir = contains(tabJeton, ouverte);
        typejeton ferme; 
        ferme.lexem=PAR_OUV;
        int fermer = contains(tabJeton, ferme);
        
        if (ouvrir > fermer) arbre[i].jeton.valeur.erreur = PAR_NONFERM;
        else if (fermer > ouvrir) arbre[i].jeton.valeur.erreur = PAR_NONOUVER;


        // test erreur 104 (double opérande)
        typejeton double_ope;
        double_ope.lexem = OPERATEUR;

        for(i=0; i<sizeof(tabJeton); i++) {
            
            if(tabJeton[i].valeur.operateur == tabJeton[i+1].valeur.operateur) {

                typejeton erreur_ope;
                erreur_ope.lexem = ERREUR;

                erreur_ope.valeur.erreur = DOUBLE_OPE;

            }
}


        // test erreur 107 (Barre non fermée pour val abs)
        typejeton barre;
        barre.lexem = BARRE;
        int doublon_absolu = contains(tabJeton, ouverte);

        if (doublon_absolu % 2 != 0) arbre[i].jeton.valeur.erreur = BAR_ABS;


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

int main () {
    Jeton tab[10];

    tab[0].lexem = REEL;
    tab[1].lexem = REEL;
    tab[0].operateur = PLUS;

    typejeton jeton;
    jeton.lexem=REEL;


    int occurence = contains(tab, jeton);
    printf("%d", occurence);


    // if (tab[0].operateur == PLUS) printf("Hello");

    // printf("%d | %f | %f", tab[0], tab[0].lexem, tab[0].operateur);

    return 0;
}

// précédent : 
// suivant : 

// Retourner le jeton d'erreur