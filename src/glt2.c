/* test.c */
#include "graph.h"
int bascule=0;
void myKey(int c) {
 switch(c) {
 case 'a':
 bascule^=1; /* La bascule passe alternativement de 0 a 1 */
 break;
 }
}
void myDraw(void) {
 /* trace une ligne blanche diagonale */
 setcolor(1.0F,1.0F,1.0F);
 line(-1.0,-1.0,1.0,1.0);
 if (bascule) {
 /* Trace un rectangle rouge a l'ecran si active
 * par appui de la touche 'a' */
 setcolor(1.0F,0.0F,0.0F);
 bar(-0.5F,-0.5F,0.5F,0.5F);
 }
 /* ecrit le message "bonjour" en jaune */
8
 setcolor(1.0F,1.0F,0.0F);
 outtextxy(0.0,0.0,"Bonjour");
}
int main(int ac,char *av[]) {
 InitGraph(ac,av,"Essai Glut",640,480,myDraw,myKey);
 return 0;
}