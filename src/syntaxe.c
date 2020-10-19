#include <stdio.h>
#include "jeton.h"
#include <math.h>

Node *syntaxe(typejeton tabJeton[], int position) {

typejeton jeton;

Node *arbre = NULL;

int i = 0;
size_t lenght = sizeof(tabJeton);

while (i != lenght) {

// erreur 104 double opérateur.

typejeton double_ope;
double_ope.lexem = OPERATEUR;

for(i=0; i<sizeof(tabJeton); i++) {

      if(tabJeton[i].valeur.operateur == tabJeton[i+1].valeur.operateur) {

        typejeton erreur_ope;
        erreur_ope.lexem = ERREUR;

        erreur_ope.valeur.erreur = DOUBLE_OPE;

      }
}

}

return arbre;

}

int main() {

return 0;
}

