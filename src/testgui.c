#include <gtk/gtk.h> 

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
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
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

    gtk_box_pack_start(GTK_BOX(hbox3), fonction, TRUE, FALSE, 50);

    image = gtk_image_new_from_file ("src/example1.png");

    gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

	gtk_main();

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    

    return 0;
}