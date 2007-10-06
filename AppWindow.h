#ifndef APPWINDOW_DEFINED
#define APPWINDOW_DEFINED

#include <gtk/gtk.h>
#include <string>
	using std::string;
#include "GeckoEmbed.h"
#include "ConfigContainer.h"

class AppWindow {

	private:
		
		void setupCallbacks(); 

		static void eventDestroy(GtkWidget* widget, gpointer data); 

		GtkWidget* window;
		GeckoEmbed gecko;

	public:

		AppWindow(int argc, char* argv[], ConfigContainer config); 
		
		~AppWindow(); 

		void setContent(GtkWidget* gtkWidget); 

		void show(); 

		void setTitle(string newTitle); 

		void start(); 
};

#endif

