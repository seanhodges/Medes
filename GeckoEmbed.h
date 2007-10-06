#ifndef GECKEMBED_DEFINED
#define GECKOEMBED_DEFINED

#include <gtk/gtk.h>
#include <gtkmozembed.h>
#include <nsEmbedAPI.h>
#include <string>
	using namespace std;

class GeckoEmbed {

	public:

		void init(); 

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

	private:

		GtkMozEmbed *mozEmbed;
};

#endif

