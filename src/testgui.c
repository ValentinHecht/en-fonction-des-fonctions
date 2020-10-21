#include <gtk/gtk.h> 

static int counter = 0;
static char renvoie_function; 

void greet(GtkWidget* widget, gpointer data) 
{ 
    /*renvoie_function = gtk_entry_get_text (fonction_entry);
    g_print("%d\n", renvoie_function);
    */
    // printf equivalent in GTK+ 
    g_print("Welcome to GTK\n"); 
    g_print("%s clicked %d times\n", 
            (char*)data, ++counter); 
}

void destroy(GtkWidget* widget, gpointer data) 
{ 
	gtk_main_quit(); 
} 

int main(int argc, char* argv[]) 
{ 

	GtkWidget* window; 
	GtkWidget* button; 
    GtkWidget *hbox;
	GtkWidget *hbox1;
	GtkWidget *hbox2;
    GtkWidget *vbox;
    GtkWidget *fonction_label;
    GtkWidget *fonction_entry;

	gtk_init(&argc, &argv); 

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 

    fonction_label = gtk_label_new("FONCTION : ");
    fonction_entry = gtk_entry_new();

    button = gtk_button_new_with_label("OK");
    g_signal_connect(GTK_OBJECT(button), 
                     "clicked", G_CALLBACK(greet), 
                     "button"); 

	hbox = gtk_hbox_new(TRUE, 5);
	hbox1 = gtk_hbox_new(TRUE, 9);
	hbox2 = gtk_hbox_new(TRUE, 10);
    vbox = gtk_vbox_new(FALSE, 30);

    gtk_box_pack_start(GTK_BOX(hbox), fonction_label, TRUE, FALSE, 50);
    gtk_box_pack_start(GTK_BOX(hbox1), fonction_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox2), button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);



	//gtk_container_add(GTK_CONTAINER(window), hbox);
    gtk_container_add(GTK_CONTAINER(window), vbox);

	

	//button = gtk_button_new_with_label("Click Me!"); 

	/*
    g_signal_connect(GTK_OBJECT(button), 
					"clicked", G_CALLBACK(greet), 
					"button"); 

	gtk_container_add(GTK_CONTAINER(window), button); 
    */
	gtk_widget_show_all(window); 

	gtk_main(); 

	return 0; 
} 


