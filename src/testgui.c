#include <gtk/gtk.h>
#include "pbPlots.h"
#include "supportLib.h"

static int counter = 0;
static char input_function[500];

const gchar *entry_text;

//Widget Main
GtkWidget* window; 
GtkWidget* button; 
GtkWidget *hbox;
GtkWidget *hbox1;
GtkWidget *hbox2;
GtkWidget *hbox3;
GtkWidget *vbox;
GtkWidget *vbox1;
GtkWidget *function_label;
GtkWidget *fonction;
GtkWidget *function_entry;
GtkWidget *image;



void greet(GtkWidget* widget, gpointer data) 
{ 
    entry_text = gtk_entry_get_text (GTK_ENTRY (function_entry));
    g_print ("Fonction entrée : %s\n", entry_text);
    if ( entry_text != "" )   
    {
        graph_print(entry_text);
    }
}



void destroy() 
{ 
	gtk_main_quit();
} 



int main(int argc, char* argv[]) 
{ 
	gtk_init(&argc, &argv); 

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GdkColor color;
    color.red = 0xffff;
    color.green = 0xffff;
    color.blue = 0xffff;
	gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 

    function_label = gtk_label_new("FONCTION : ");
    function_entry = gtk_entry_new();

    button = gtk_button_new_with_label("OK");
    g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(greet), "button"); 

    //Déclaration et positionnement des éléments présents dans la fenêtre
	hbox = gtk_hbox_new(TRUE, 5);
	hbox1 = gtk_hbox_new(TRUE, 9);
	hbox2 = gtk_hbox_new(TRUE, 10);
    vbox = gtk_vbox_new(FALSE, 30);

    gtk_box_pack_start(GTK_BOX(hbox), function_label, TRUE, FALSE, 50);
    gtk_box_pack_start(GTK_BOX(hbox1), function_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox2), button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);

	//gtk_container_add(GTK_CONTAINER(window), hbox);
    gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_widget_show_all(window); 

	gtk_main(); 

	return 0; 
} 



void graph_print(char input_f[], int argc, char* argv[], GtkWidget* widget, gpointer data)
{

    fonction = gtk_label_new(input_f);

    gtk_init(&argc, &argv); 

    gtk_container_remove(GTK_CONTAINER(window), vbox); // Remove previous window

    hbox3 = gtk_hbox_new(TRUE, 10);
    vbox = gtk_vbox_new(FALSE, 30);
    vbox1 = gtk_vbox_new(FALSE, 30);

    gtk_box_pack_start(GTK_BOX(hbox3), fonction, TRUE, FALSE, 10);

    graph_draw();

    image = gtk_image_new_from_file ("src/graph.png");

    gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

	gtk_main();

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    

    return 0;
}


void graph_draw()
{

	double xs [] = {-10, -1, 0, 1, 10}; // Ici récup série de point des autres parties du programme
	double ys [] = {6, -2, -2, -1, 2};

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
    settings->width = 600;
	settings->height = 400;
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
	DrawScatterPlot(canvasReference, 600, 400, xs, 5, ys, 5);

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "src/graph.png");
	DeleteImage(canvasReference->image);

	return 0;
}