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
	bool ruleFound = false;
	bool cancelRedirect = true;
	string target = uri;
	deque<GroupedEntry> domainRules = parent.getConfig().getDomainRules();
	for (deque<GroupedEntry>::iterator it = domainRules.begin(); it != domainRules.end(); it++) {
		GroupedEntry entry = *it;
		if (target.find(entry.getValue()) == 0) {
			// A target rule has been found (break after valid rule)
			if (entry.getGroup() == "internal") {
				cout << "page redirection to: " + target << endl;
				cancelRedirect = false;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "external") {
				cout << "executing handler for domain: " + target << endl;
				string cmd = "gnome-www-browser " + target;
				system(cmd.c_str());
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "advert") {
				cout << "dropping advert: " + target << endl;
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "drop") {
				cout << "dropping domain target: " + target << endl;
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else {
				cout << "(!!!) ignoring unknown target rule: " + entry.getGroup() << endl;
			}
		}
	}
	if (!ruleFound) {
		cout << "(!!!) no rule set for target domain: " + target << endl;
	}
	return cancelRedirect;
}
