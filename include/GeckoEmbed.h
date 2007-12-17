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
#include "StatusBar.h"

class GeckoEmbed {

	private:

		GtkMozEmbed* mozEmbed;
		ConfigContainer config;
		StatusBar *status;
		int dataSize;

	public:

		void init(ConfigContainer config); 
		void bringUp(); 
		void tearDown(); 

		GtkWidget* getFrame(); 
		ConfigContainer getConfig() { return config; }
		GtkMozEmbed* getMozEmbed() const { return mozEmbed; }
		StatusBar *getStatusBar() { return status; }
		int getDataSize() { return dataSize; }

		void setConfig(const ConfigContainer& newConfig) { config = newConfig; }
		void setUrl(const string& newUrl); 
		void setMozEmbed(GtkMozEmbed* newMoz) { mozEmbed = newMoz; }
		void attachStatusBar(StatusBar *status);
		void setDataSize(int dataSize) { this->dataSize = dataSize; }

		static gint open_uri_cb(GtkMozEmbed *embed, const char *uri, GeckoEmbed& parent);
		static void progress_change_cb(GtkMozEmbed *embed, gint cur, gint max, GeckoEmbed& parent);
		static void load_started_cb(GtkMozEmbed *embed, GeckoEmbed& parent);
		static void load_finished_cb(GtkMozEmbed *embed, GeckoEmbed& parent);

};

#endif

