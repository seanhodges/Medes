#include <gtk/gtk.h>

#include <string>
using namespace std;

class AppWindow {

	public:

		/*
		 * Create the application window
		 *
		 * @param argc - number of arguments passed into main()
		 * @param argv[] - the arguments passed into main()
		 */
		AppWindow(int argc, char *argv[]) {
			gtk_init(&argc, &argv);
			window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
			setTitle("Google Maps");
			setupCallbacks();
		}

		/**
		 * Attach an embedded Gecko browser
		 */
		void attachBrowser(GtkWidget *mozEmbedContainer) {
			gtk_container_add(GTK_CONTAINER(window), mozEmbedContainer);
		}

		/*
		 * Show the application window
		 */
		void show(void) {
			gtk_widget_show_all(window);
		}

		/*
		 * Change the title on the window
		 *
		 * @param newTitle - the new title to display
		 */
		void setTitle(string newTitle) {
			gtk_window_set_title(GTK_WINDOW (window), newTitle.c_str());
		}

		/*
		 * Run the gtk_main() loop (event handler)
		 */
		void start(void) {
			gtk_main();
		}

	private:
		
		/*
		 * Set-up the event callbacks handled in this window
		 */
		void setupCallbacks(void) {
			g_signal_connect(G_OBJECT (window), "destroy", G_CALLBACK(eventDestroy), NULL);
		}

		/*
		 * Destroy this window (handled internally by an event)
		 *
		 * @param *widget - reference to the window object
		 * @param data - unused data from glib
		 */
		static void eventDestroy(GtkWidget *widget, gpointer data) {
			gtk_main_quit();
		}

		GtkWidget *window;
};

