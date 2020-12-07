#include <gtk/gtk.h>
#include<stdio.h>
#include "pbPlots.h"
#include "supportLib.h"

//Variable(s)

const gchar *entry_text;

//Affichage Gtk Menu

GtkWidget *window;
GtkWidget *affi_box;
GtkWidget *fonction_entry;
GtkWidget *boutton1;

// Affichage Gtk Graph

GtkWidget *window2;
GtkWidget *name_fonction;
GtkWidget *afimg;
GdkPixbuf* image;

// Gtk Divers

GtkBuilder *builder;
GtkWidget *window3;
GtkWidget *pixbuf;

// Fonction d'afficahge du Menu
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/test2.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

	GdkColor color;
    color.red = 0xffff;
    color.green = 0xffff;
    color.blue = 0xffff;
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    affi_box = GTK_WIDGET(gtk_builder_get_object(builder, "affi_box"));
    fonction_entry = GTK_WIDGET(gtk_builder_get_object(builder, "fonction_entry"));
    boutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "boutton_ok"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

// Fonction qui gère lorqu'on clique sur le bouton OK dans le Menu
void on_boutton_ok_clicked (GtkButton *b)
{
    entry_text = gtk_entry_get_text (GTK_ENTRY (fonction_entry));
    g_print ("Fonction entrée : %s\n", entry_text);
    graph_draw(entry_text, 600, 400);
}

void graph_draw(char name_function, int width_graph, int height_graph, int argc, char *argv[])
{
	//récupération des points de la fonction pour les placer sur le graph
	double xs [] = {-5, -1, 0, 1, 2};
	double ys [] = {2, -1, -2, -1, 2};

	//génération des axes
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = xs;
	series->xsLength = 5;
	series->ys = ys;
	series->ysLength = 5;
	series->linearInterpolation = true;
	series->lineType = L"dashed";
	series->lineTypeLength = wcslen(series->lineType);
	series->lineThickness = 2;
	series->color = GetGray(0.3);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = width_graph;
	settings->height = height_graph;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
  	settings->xLabel = L"X axis";
  	settings->xLabelLength = wcslen(settings->xLabel);
  	settings->yLabel = L"Y axis";
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
    graph_print_resizable();
}

//Fonction d'affichage du graph
void graph_print()
{
    //name_fonction = gtk_label_new(input_f);

    gtk_widget_destroy(GTK_WIDGET(window));

    builder = gtk_builder_new_from_file("src/test3.glade");

    window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    GdkColor color;
    color.red = 0xffff;
    color.green = 0xffff;
    color.blue = 0xffff;
    gtk_widget_modify_bg(window2, GTK_STATE_NORMAL, &color);
    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);

    // Test d'affichage du graph
    // int image = "src/graph.png";

    gtk_widget_show(window2);
    // g_signal_connect(container, "size-allocate", G_CALLBACK(resize_image), widgets);
    
    gtk_main();
}

void on_boutton_menu_clicked (GtkButton *b)
{
    gtk_widget_destroy(GTK_WIDGET(window2));
    main(1, 2);
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

int graph_print_resizable()
{
  GtkWidget *window3=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window3), "Resize Picture");
  gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window3), 600, 400);

  g_signal_connect(window3, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //Needs a valid picture.
  GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file("src/graph.png", NULL);

  GtkWidget *da1=gtk_drawing_area_new();
  gtk_widget_set_hexpand(da1, TRUE);
  gtk_widget_set_vexpand(da1, TRUE);
  g_signal_connect(da1, "draw", G_CALLBACK(draw_picture), pixbuf);

  GtkWidget *grid=gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), da1, 0, 0, 1, 1);

  gtk_container_add(GTK_CONTAINER(window3), grid);
  gtk_widget_show_all(window3);

  gtk_main();

  g_object_unref(pixbuf);

  return 0;
}