#include <gtk/gtk.h>
#include "pbPlots.h"
#include "supportLib.h"

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
int main(int argc, char *argv[])
{
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

    return EXIT_SUCCESS;
}

// Fonction qui gère lorqu'on clique sur le bouton OK dans le Menu
void on_boutton_ok_clicked (GtkButton *b, GtkWidget *window)
{
    entry_fonction = gtk_entry_get_text (GTK_ENTRY (fonction_entry));
    entry_borne_basse = gtk_entry_get_text (GTK_ENTRY (borne_basse));
    entry_borne_haute = gtk_entry_get_text (GTK_ENTRY (borne_haute));
    entry_pas_fonction = gtk_entry_get_text (GTK_ENTRY (pas_fonction));
    g_print ("Fonction entrée : %s\nBorne Basse : %s\nBorne Haute : %s\nPas de la fonction : %s\n", entry_fonction, entry_borne_basse, entry_borne_haute, entry_pas_fonction);
    
    /* 
    if(scanf("%d%d%d", &entry_borne_basse, &entry_borne_haute, &entry_pas_fonction) != 3 || (entry_fonction != NULL) && (entry_fonction[0] == '\0'))
    {
        printf("failure\n");
    }
    else
    {
        printf("Entrée semble ok\n");
    } */

    int entry_borne_basse_int = atoi(entry_borne_basse);
    int entry_borne_haute_int = atoi(entry_borne_haute);
    int entry_pas_fonction_int = atoi(entry_pas_fonction);
    printf("%d\n", entry_pas_fonction_int);
    graph_draw(entry_fonction, entry_borne_basse_int, entry_borne_haute_int, entry_pas_fonction_int, 1280, 720, window);
}

void graph_draw(char name_fonction, int borne_basse, int borne_haute, int pas_fonction, int width_graph, int height_graph, GtkWidget *window)
{
	//récupération des points de la fonction pour les placer sur le graph
	double xs [] = {-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10};
	double ys [] = {-3,-4,-5,-4,-3,-2,-1,0,1,2,1,2,3,4,5,6,7,8,9,10,11};
    //double xs [] = {nom variable qui donnera la suite de nombre des valeurs de x};
	//double ys [] = {nom variable qui donnera la suite de nombre des valeurs de y};

    printf("%d", pas_fonction);

	//génération des axes
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = xs;
	series->xsLength = pas_fonction;
	series->ys = ys;
	series->ysLength = pas_fonction;
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
	WriteToFile(pngdata, length, "src/graph.png");
	DeleteImage(canvasReference->image);

	//graph_print();
    graph_print_resizable(name_fonction, window);
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
void graph_print_resizable(char name_fonction, GtkWidget *window)
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

    gtk_widget_destroy(window);
    
    gtk_widget_show_all(window2);

    gtk_main();

    g_object_unref(pixbuf);

    return 0;
}
