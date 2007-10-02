#include <gtk/gtk.h>
#include <gtkmozembed.h>
#include <nsEmbedAPI.h>

#include <string>
using namespace std;

class GeckoEmbed {

	public:

		/*
		 * Initialise gtkmozembed
		 */
		GeckoEmbed() {
			gtk_moz_embed_set_profile_path("mozembed","mozembed");
			mozEmbed = GTK_MOZ_EMBED(gtk_moz_embed_new());
		}

		/*
		 * Provide a GTK hbox containing a gtkmozembed object
		 *
		 * @return the GTK hbox instance
		 */
		GtkWidget *getFrame(void) {
			GtkWidget *mozEmbedContainer = gtk_hbox_new(0, 0);
			gtk_box_pack_start(GTK_BOX(mozEmbedContainer), GTK_WIDGET(mozEmbed), TRUE, TRUE, 0);
			return mozEmbedContainer;
		}

		/*
		 * Redirect the Gecko engine to a given address
		 *
		 * @param newUrl - a fully resolved URL
		 */
		void setUrl(string newUrl) {
			gtk_moz_embed_load_url(mozEmbed, newUrl.c_str());
		}

		/*
		 * Start the Gecko engine (must call before gtk_main())
		 */
		void bringUp(void) {
			gtk_moz_embed_push_startup();
		}

		/*
		 * Stop the Gecko engine (must call after gtk_main())
		 */
		void tearDown(void) {
			gtk_moz_embed_pop_startup();
		}

	private:

		GtkMozEmbed *mozEmbed;
};

