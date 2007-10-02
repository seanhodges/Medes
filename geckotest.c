#include <gtk/gtk.h>
#include <stdbool.h>
#include <gtkmozembed.h>
#include <nsEmbedAPI.h>

//static bool mozillaInit(void);

/* Handle window close event */
static void destroy(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *mozEmbedContainer;
	GtkMozEmbed *mozEmbed; 

	// Initialise gtkmozembed
	gtk_moz_embed_set_profile_path(".","mozembed");

	// Initialise GTK
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_set_title(GTK_WINDOW (window), "Google Maps");
    
	// Create the gtkmozembed widget
	mozEmbed = GTK_MOZ_EMBED (gtk_moz_embed_new());
	mozEmbedContainer = gtk_hbox_new(0, 0);
	gtk_box_pack_start(GTK_BOX(mozEmbedContainer), GTK_WIDGET(mozEmbed), TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), mozEmbedContainer);
    
	// Post-configuration
   	gtk_moz_embed_load_url(mozEmbed, "http://maps.google.co.uk");
    
	/* Handle close and destroy of window */
    g_signal_connect(G_OBJECT (window), "destroy",
		      G_CALLBACK(destroy), NULL);
    
    /* Show the window */
    gtk_widget_show_all(window);
	gtk_moz_embed_push_startup();
    gtk_main();
	gtk_moz_embed_pop_startup();

    return 0;
}
