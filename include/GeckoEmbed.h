#ifndef GECKEMBED_DEFINED
#define GECKOEMBED_DEFINED

#include <gtk/gtk.h>
#include <gtkmozembed.h>
#include <nsEmbedAPI.h>
#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include <stdlib.h>
#include "ConfigContainer.h"

class GeckoEmbed {

	private:

		GtkMozEmbed* mozEmbed;
		ConfigContainer config;

	public:

		void init(ConfigContainer config); 

		GtkWidget* getFrame(); 
		ConfigContainer getConfig() { return config; }

		void setConfig(const ConfigContainer& newConfig) { config = newConfig; }
		void setUrl(const string& newUrl); 

		void bringUp(); 
		void tearDown(); 

		GtkMozEmbed* getMozEmbed() const {
			return mozEmbed;
		}

		void setMozEmbed(GtkMozEmbed* newMoz) {
			mozEmbed = newMoz; 
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
		static gint open_uri_cb(GtkMozEmbed *embed, const char *uri, GeckoEmbed& parent) {
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
						break;
					}
					else if (entry.getGroup() == "external") {
						cout << "executing handler for domain: " + target << endl;
						string cmd = "gnome-www-browser " + target;
						system(cmd.c_str());
						cancelRedirect = true;
						break;
					}
					else if (entry.getGroup() == "advert") {
						cout << "dropping advert: " + target << endl;
						cancelRedirect = true;
						break;
					}
					else if (entry.getGroup() == "drop") {
						cout << "dropping domain target: " + target << endl;
						cancelRedirect = true;
						break;
					}
					else {
						cout << "ignoring unknown target rule: " + entry.getGroup() << endl;
					}
				}
			}
			return cancelRedirect;
		}
};

#endif

