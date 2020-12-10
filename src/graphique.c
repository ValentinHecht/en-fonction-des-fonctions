#include <gtk/gtk.h>
#include "pbPlots.h"
#include "supportLib.h"
#include "graphique.h"

//Variable(s)

gchar *entry_fonction;
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


// Fonction d'afficahge du Menu


// Fonction qui gère lorqu'on clique sur le bouton OK dans le Menu


void graph_draw(char name_fonction, float resultat[200][2], int taille_tableau, int width_graph, int height_graph)
{
	//récupération des points de la fonction pour les placer sur le graph
    double xs [taille_tableau];
	double ys [taille_tableau];

    for (int i=0;i<taille_tableau;i++)
    {
        xs[i]=resultat[i][0];
        ys[i]=resultat[i][1];
    }
    
	//génération des axes
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = xs;
	series->xsLength = taille_tableau;
	series->ys = ys;
	series->ysLength = taille_tableau;
	series->linearInterpolation = true;
	//series->lineType = L"dashed";
	series->lineTypeLength = wcslen(series->lineType);
	series->lineThickness = 2;
	series->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = width_graph;
	settings->height = height_graph;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
  	settings->xLabel = L"axe X";
  	settings->xLabelLength = wcslen(settings->xLabel);
  	settings->yLabel = L"axe Y";
  	settings->yLabelLength = wcslen(settings->yLabel);
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlotFromSettings(canvasReference, settings);

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "./graph.png");
	DeleteImage(canvasReference->image);

	//graph_print();
    graph_print_resizable(name_fonction);
}

gboolean draw_picture(GtkWidget *da, cairo_t *cr, gpointer data)
{
    gint width=gtk_widget_get_allocated_width(da);
    gint height=gtk_widget_get_allocated_height(da);

    GdkPixbuf *temp=gdk_pixbuf_scale_simple((GdkPixbuf*)data, width, height, GDK_INTERP_BILINEAR);
    gdk_cairo_set_source_pixbuf(cr, temp, 0, 0);
    cairo_paint(cr);

    g_object_unref(temp);
    return FALSE;
}

void button_box_action (GtkWidget *button)
{
    gtk_widget_destroy(window2);
    main(1,1);
}

// affichage du Graph et possibilité de resizer et l'image suit
void graph_print_resizable(char name_fonction)
{
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "En Fonction des Fonctions");

    GdkColor color;
    color.red = 0xffff;
    color.green = 0xffff;
    color.blue = 0xffff;
    gtk_widget_modify_bg(window2, GTK_STATE_NORMAL, &color);

    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window2), 800, 600);

    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label ("Retour au Menu");
    gtk_container_add (GTK_CONTAINER (button_box), button);
    g_signal_connect(button, "clicked", G_CALLBACK(button_box_action), NULL);

    // Image valide nécessaire
    pixbuf = gdk_pixbuf_new_from_file("src/graph.png", NULL);

    da1 = gtk_drawing_area_new();
    gtk_widget_set_hexpand(da1, TRUE);
    gtk_widget_set_vexpand(da1, TRUE);
    g_signal_connect(da1, "draw", G_CALLBACK(draw_picture), pixbuf);

    grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), da1, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_box, 0, 1, 1, 1);

    gtk_container_add(GTK_CONTAINER(window2), grid);
    
    gtk_widget_show_all(window2);

    gtk_main();

    g_object_unref(pixbuf);

    return 0;
}
