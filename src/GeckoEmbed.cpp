#include <stdlib.h>
#include "GeckoEmbed.h"

/**
 * Initialise the engine (must be called AFTER gtk_init())
 */
void GeckoEmbed::init(ConfigContainer config) {
	// Set the environment
	string userHome = getenv("HOME");
	string configProfilePath = userHome + "/.mozilla/medes";
	string configProfileName = "medes-default";
	gtk_moz_embed_set_profile_path(configProfilePath.c_str(),configProfileName.c_str());
	GtkMozEmbed *mozEmbed = GTK_MOZ_EMBED(gtk_moz_embed_new());
	gtk_moz_embed_set_chrome_mask(mozEmbed, GTK_MOZ_EMBED_FLAG_ALLCHROME);
	// Attach to functors
	gtk_signal_connect(GTK_OBJECT(mozEmbed), "open_uri", GTK_SIGNAL_FUNC(&GeckoEmbed::open_uri_cb), this);
	// Initial object configuration
	GeckoEmbed::setMozEmbed(mozEmbed);
	GeckoEmbed::setConfig(config);
	GeckoEmbed::setUrl(config.getAppUrl());
}

/**
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

/**
 * Redirect the Gecko engine to a given address
 *
 * @param newUrl - a fully resolved URL
 */
void GeckoEmbed::setUrl(const string& newUrl) {
	gtk_moz_embed_load_url(GeckoEmbed::getMozEmbed(), newUrl.c_str());
}

/**
 * Start the Gecko engine (must call before gtk_main())
 */
void GeckoEmbed::bringUp() {
	gtk_moz_embed_push_startup();
}

/**
 * Stop the Gecko engine (must call after gtk_main())
 */
void GeckoEmbed::tearDown() {
	gtk_moz_embed_pop_startup();
}
