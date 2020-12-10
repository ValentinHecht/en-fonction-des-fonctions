/*******************************************************************************************
* En fonction des fonctions

* Romain Larramendy, Lucas Bremard, Killian Baert, Valentin Hecht, Thomas Tissier, Maxence Dhaynaut, Benjamin Chane, Louis-Marie Bossard 

* FISA-TI23 Copyright 2020-2020
********************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>

#include "evaluateur.h"
#include "newsyntaxe.h"
#include "lexical.h"
#include "pbPlots.h"
#include "supportLib.h"
#include "graphique.h"

//Variable(s)

char *entry_fonction;
int *entry_borne_basse;
int *entry_borne_haute;
int *entry_pas_fonction;

//Affichage Gtk Menu

GtkWidget *window;
GtkWidget *fonction_entry;
GtkWidget *borne_basse;
GtkWidget *borne_haute;
GtkWidget *pas_fonction;
GtkWidget *boutton1;

// Affichage Gtk Graph

GtkWidget *window2;
GtkWidget *pixbuf;
GtkWidget *da1;
GdkPixbuf* grid;
GtkWidget *button;
GtkWidget *button_box;

// Gtk Divers

GtkBuilder *builder;


int main(int argc, char const *argv[])
{

    /*
    printf("Entrez votre fonction : ");
    scanf("%s", operation);
    printf("Entrez votre premiere borne : ");
    scanf("%lf", &borneStart);
    printf("Entrez votre deuxieme borne : ");
    scanf("%lf", &borneEnd);
    */

    //Partie graphique entrée fonc
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("../test2.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //g_signal_connect(window, "", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

	GdkColor color;
    color.red = 0xffff;
    color.green = 0xffff;
    color.blue = 0xffff;
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    borne_basse = GTK_WIDGET(gtk_builder_get_object(builder, "borne_basse"));
    borne_haute = GTK_WIDGET(gtk_builder_get_object(builder, "borne_haute"));
    pas_fonction = GTK_WIDGET(gtk_builder_get_object(builder, "pas_fonction"));
    fonction_entry = GTK_WIDGET(gtk_builder_get_object(builder, "fonction_entry"));
    boutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "boutton_ok"));

    gtk_widget_show(window);

    gtk_main();
    //on_boutton_ok_clicked(boutton1, window);
    
/*     void on_boutton_ok_clicked (GtkButton *b, GtkWidget *window)
    {
        // test purpose
    } */
        return 0; 
}


void on_boutton_ok_clicked (GtkButton *b, GtkWidget *window)
{
    float couples[200][2];
    int tab_compteur = 0;


    entry_fonction = gtk_entry_get_text (GTK_ENTRY (fonction_entry));
    entry_borne_basse = gtk_entry_get_text (GTK_ENTRY (borne_basse));
    entry_borne_haute = gtk_entry_get_text (GTK_ENTRY (borne_haute));
    entry_pas_fonction = gtk_entry_get_text (GTK_ENTRY (pas_fonction));

    int entry_borne_basse_int = atoi(entry_borne_basse);
    int entry_borne_haute_int = atoi(entry_borne_haute);
    int entry_pas_fonction_int = atoi(entry_pas_fonction);

    printf("%s %d %d %d\n", entry_fonction, entry_borne_basse_int, entry_borne_haute_int, entry_pas_fonction_int);
   
    printf("%s\n", entry_fonction);
    
    //Partie lexicale
    printf("je suis 1\n");
    Jeton* jetons_lexi = malloc(sizeof(Jeton));
    jetons_lexi = analyse_lexical(entry_fonction);
    printf("je suis 2\n");
    
    
    // Partie syntaxe
    
    printf("\n\n");

    printf("%d\n", sizeof(Jeton));

    Arbre *arbre = malloc(sizeof(Arbre));
    printf("tetetsttfefvjzhefvjhve\n");
    arbre = syntaxe(jetons_lexi, get_length_tableau()-1);

    /*for (int a = 0; a < get_length_tableau()-1; a++) {
        printf("test for for ");
        printf("\nvaleur: %d", jetons_lexi[a].lexem);
        
    } */
    
    printf("%d\n", sizeof(arbre));
    printf("je suis 3\n");
    printf("\nFin partie syntax\n\n");
    
    int i = entry_borne_basse;
    int max = entry_borne_haute;
    while(arbre->couche!=0)
    {
        arbre=arbre->pjetonparent;
    }
    printf("je suis 4\n");
    // Partie Evaluateur
    if (get_erreur_syntaxe() == 0) // get erre
    {
        printf("je suis 5\n");
        for (i; i <= max; i++)
        {
            couples[tab_compteur][0] = i;                    // Valeurs de x
            couples[tab_compteur][1] = fonc_eval(arbre, i);  // Valeurs de f(x)
            tab_compteur++;
        }
        for (int y = 0; y < tab_compteur; y++)
        {
            printf("Valeur de x    : %f\n", couples[y][0]);
            printf("Valeur de f(x) : %f\n", couples[y][1]);
            printf("\n");
        }
        printf("\nTaille du tableau : %d\n\n", get_length_tableau()-1);

        printf("\nFin partie evalu\n");
    }

    // Dans partie graphique
    if (get_erreur_syntaxe())
    {
        gtk_widget_destroy(window);
    }
    else
    {
        // Partie graphe affichage
        gtk_widget_destroy(window);
        printf("yoyo je dessine le graph\n");
        graph_draw(entry_fonction, couples, tab_compteur, 1280, 720);
    }
    free(jetons_lexi);
    free(arbre);
}
