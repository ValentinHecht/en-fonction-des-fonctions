#include <stdio.h>


int main() {

Noeud*syntax(fg, fd, jeton);
Noeud*Arbre = NULL;
Noeud*temp;
int i=0, j=0;

while (tab[i].lexeme)

    switch (tab[j].lexeme) {

    case Reel : case Var; :

    {

    Arbre = creerNoeud(tab[j], NULL, NULL);

    j++;

    break;

    }

    case oper : {

    i* = j++;

    temp = syntax(tab[j], i);
    Arbre = creerNoeud(tab[j], Arbre, temp);

    break;

    }

    case function {

    i* = j++;

    temp = syntax(tab[j], i)
    Arbre = creerNoeud(tab[j], temp, NULL);

    j++;

    break;

    }

    case par_ouv {

        j++;

        Arbre = syntax(tab[j], j);

    break;

    }

    case par_fer {

        j++;

        Arbre = syntax(tab[j], j);

    break;

    }

    }

    return 0;
}
