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
			vector<string> domainList = parent.getConfig().getDomainList();
			for (vector<string>::iterator allowed = domainList.begin(); allowed != domainList.end(); ++allowed) {
				if (target.find(*allowed) == 0) {
					cancelRedirect = false;
				}
			}
			if (cancelRedirect) {
				cout << "executing handler for domain: " + target << endl;
				string cmd = "gnome-www-browser " + target;
				system(cmd.c_str());
			}
			else {
				cout << "page redirection to: " + target << endl;
			}
			return cancelRedirect;
		}
};

#endif

