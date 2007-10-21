#include "gtkmozembed.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv)
{
	GtkWidget *topLevelWindow;
	GtkWidget *topLevelVBox;
	GtkWidget *mozEmbed;

	gtk_set_locale();
	gtk_init(&argc, &argv);
	//gtk_moz_embed_set_profile_path("/home/glantz/thumbserver", "test");
	// create our new toplevel window
	topLevelWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// new vbox
	topLevelVBox = gtk_vbox_new(FALSE, 0);
	// add it to the toplevel window
	gtk_container_add(GTK_CONTAINER(topLevelWindow),topLevelVBox);
	// add mozilla
	mozEmbed = gtk_moz_embed_new();
	// add it to the toplevel vbox
	gtk_box_pack_start(GTK_BOX(topLevelVBox), mozEmbed, TRUE, TRUE, 0);
	gtk_moz_embed_set_chrome_mask(GTK_MOZ_EMBED(mozEmbed), GTK_MOZ_EMBED_FLAG_ALLCHROME);
	//size the widget
	gtk_widget_set_usize(mozEmbed, 800, 600);
	//gtk_moz_embed_load_url(GTK_MOZ_EMBED(mozEmbed), argv[1]);
	// show the widgets
	gtk_widget_show(topLevelWindow);
	gtk_widget_show(topLevelVBox);
	gtk_widget_show(mozEmbed);
	//gtk_moz_embed_load_url(GTK_MOZ_EMBED(mozEmbed), argv[1]);
	gtk_main ();
	return 0;
}
