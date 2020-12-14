Bienvenue dans grapheur, un projet de groupe de la promotion FISA-TI23 avec comme membres :
Killian Baert & Maxence Dhaynaut, Lucas Bremard & Benjamin Chane-Law, Louis-Marie Bossard & Valentin Hecht, Romain Larramendy & Thomas Tissier.

Ce projet a pour but d'afficher une courbe saisie par un utilisateur sur une borne inferieure et superieure egalement definies par l'utilisateur. Ce dernier a la possibilite de zoomer dans la courbe afin d'obtenir des valeurs precises.

/!\ ATTENTION /!\ :
L'application n'est pas finie car nous avons rencontré des difficultés au moment du regroupement des parties.
Nous avons donc 2 programmes :
- Un lexsyneva pour les partie Lexicale, Syntaxique et Evaluateur
- Un graphique pour la partie graphique seulement

Pour la partie graphique, l'installation de GTK est requise :
installer gtk 3 sous ubuntu :
- sudo apt-get install libgtk-3-dev


Pour utiliser le programme voici les etapes a suivre :

- Lancer le programme <code>lexsyneva.exe</code> ou bien <code>./lexsyneva</code> ou <code>graphique.exe</code> ou bien <code>./graphique</code> ;
- Saisissez votre fonction sans oublier un operateur entre chaque membre de votre fonction. Exemple : <code>sin(x)*cos(x)</code>;
- Saisissez la borne inferieure et superieure dans la meme fenetre ainsi que le pas de votre fonction;
- Enfin, cliquez sur OK afin d'afficher la courbe de votre fonction.

Pour saisir une nouvelle fonction, un bouton indiquant <code>Retourner au menu</code> s'affiche en bas de la fenetre.



