#include "GeckoEmbed.h"

/**
 * Initialise the engine (must be called AFTER gtk_init())
 */
void GeckoEmbed::init(ConfigContainer config) {
	string configProfilePath = "mozembed";
	string configProfileName = "mozembed";
	gtk_moz_embed_set_profile_path(configProfilePath.c_str(),configProfileName.c_str());
	GtkMozEmbed *mozEmbed = GTK_MOZ_EMBED(gtk_moz_embed_new());
	GeckoEmbed::setMozEmbed(mozEmbed);
	GeckoEmbed::setUrl(config.getAppUrl());
}

/*
 * Provide a GTK hbox containing a gtkmozembed object
 *
 * @return the GTK hbox instance
 */
GtkWidget* GeckoEmbed::getFrame() {
	GtkWidget* mozEmbedContainer = gtk_hbox_new(0, 0);
	gtk_box_pack_start(
		GTK_BOX(mozEmbedContainer), 
		GTK_WIDGET(GeckoEmbed::getMozEmbed()), 
		TRUE, TRUE, 0);
	return mozEmbedContainer;
}

/*
 * Redirect the Gecko engine to a given address
 *
 * @param newUrl - a fully resolved URL
 */
void GeckoEmbed::setUrl(string newUrl) {
	gtk_moz_embed_load_url(GeckoEmbed::getMozEmbed(), newUrl.c_str());
}

/*
 * Start the Gecko engine (must call before gtk_main())
 */
void GeckoEmbed::bringUp() {
	gtk_moz_embed_push_startup();
}

/*
 * Stop the Gecko engine (must call after gtk_main())
 */
void GeckoEmbed::tearDown() {
	gtk_moz_embed_pop_startup();
}

