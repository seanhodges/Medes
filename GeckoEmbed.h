#ifndef GECKEMBED_DEFINED
#define GECKOEMBED_DEFINED

#include <gtk/gtk.h>
#include <gtkmozembed.h>
#include <nsEmbedAPI.h>
#include <string>
	using std::string;
#include "ConfigContainer.h"

class GeckoEmbed {

	private:

		GtkMozEmbed *mozEmbed;

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
};

#endif

