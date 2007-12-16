#include <stdlib.h>
#include "GeckoEmbed.h"
#include "Environment.h"
#include "Rules.h"

/**
 * Initialise the engine (must be called AFTER gtk_init())
 */
void GeckoEmbed::init(ConfigContainer config) {
	// Set the environment
	Environment env;
	string configProfilePath = env.getUserGeckoProfilePath();
	string configProfileName = "medes-gecko";
	gtk_moz_embed_set_profile_path(configProfilePath.c_str(),configProfileName.c_str());
	GtkMozEmbed *mozEmbed = GTK_MOZ_EMBED(gtk_moz_embed_new());
	gtk_moz_embed_set_chrome_mask(mozEmbed, GTK_MOZ_EMBED_FLAG_ALLCHROME);
	// Attach to functors
	gtk_signal_connect(GTK_OBJECT(mozEmbed), "open_uri", GTK_SIGNAL_FUNC(&GeckoEmbed::open_uri_cb), this);
	gtk_signal_connect(GTK_OBJECT(mozEmbed), "progress", GTK_SIGNAL_FUNC(&GeckoEmbed::progress_change_cb), this);
	// Initial object configuration
	setMozEmbed(mozEmbed);
	setConfig(config);
	setUrl(config.getAppUrl());
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

/**
 * Callback event for page redirection
 *
 * @param embed - the mozilla object
 * @param uri - the new URL passed to the engine
 * @param parent - the parent instance for this callback
 *
 * @return true to stop redirection event, otherwise false
 */
gint GeckoEmbed::open_uri_cb(GtkMozEmbed *embed, const char *uri, GeckoEmbed& parent) {
	string target = uri;
	Rules *handler;
	// Determine which rules to run
	if (target.find("http:") == 0 
			|| target.find("https:") == 0 
			|| target.find("about:") == 0 
			|| target.find("ftp:") == 0) {
		cout << "applying http rules" << endl;
		handler = new HttpRules(parent.getConfig());
	}
	else if (target.find("javascript:") == 0) {
		cout << "applying javascript rules" << endl;
		handler = new JavascriptRules(parent.getConfig());
	}
	else {
		// URL support is limited to what the rules understand
		cout << "an unsupported url was passed to the rules engine" << endl;
		cout << "url string was: " << target << endl;
		exit(1);
	}
	handler->runRules(target);
	bool redirect = handler->isRedirectAllowed();
	delete handler;
	return !redirect;
}

void GeckoEmbed::progress_change_cb(GtkMozEmbed *embed, gint cur, gint max, GeckoEmbed& parent) {
	cout << "loading progress " << cur << "B / " << max << "B" << endl;
}
