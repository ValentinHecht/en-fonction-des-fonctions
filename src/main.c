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



int main(int argc, char const *argv[])
{
    float couples[200][2];
    int tab_compteur = 0;
    Node Node_1;
    char operation[30];

    
    printf("Entrez votre fonction : ");
    scanf("%s", operation);
    printf("Entrez votre premiere borne : ");
    scanf("%lf", &borneStart);
    printf("Entrez votre deuxieme borne : ");
    scanf("%lf", &borneEnd);

    //Partie graphique entrée fonc
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/test2.glade");

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

    


    //Partie lexicale
    Jeton* jetons_lexi = analyse_lexical(operation);

    // Partie syntaxe
    Node *arbre;
    printf("\n\n");
    arbre  = syntaxe(jetons_lexi, get_length_tableau()-1);
    printf("\nFin partie syntax\n\n");
    float i = borneStart;
    float max = borneEnd;
    while(arbre->couche!=0)
    {
        arbre=arbre->pjetonparent;
    }
    
    // Partie Evaluateur
    if (get_erreur_syntaxe() == 0) // get erre
    {
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
        
    }
    else
    {
        // Partie graphe affichage
        graph_draw(entry_fonction, entry_borne_basse_int, entry_borne_haute_int, entry_pas_fonction_int, 1280, 720);
    }

    return 0; 
}
