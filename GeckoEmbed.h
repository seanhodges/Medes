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
#include "ConfigContainer.h"

class GeckoEmbed {

	private:

		GtkMozEmbed* mozEmbed;

	public:

		void init(ConfigContainer config); 

		GtkWidget* getFrame(); 

		void setUrl(string newUrl); 

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
		 * @param dummy - this is not used
		 *
		 * @return true to stop redirection event, otherwise false
		 */
		static gint open_uri_cb(GtkMozEmbed *embed, const char *uri, bool dummy) {
			cout << "page redirection detected" << endl;
			return false;
		}
};

#endif

