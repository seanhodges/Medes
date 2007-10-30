#ifndef GECKOEMBED_DEFINED
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

		static gint open_uri_cb(GtkMozEmbed *embed, const char *uri, GeckoEmbed& parent);

};

#endif

