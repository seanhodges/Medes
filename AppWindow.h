#ifndef APPWINDOW_DEFINED
#define APPWINDOW_DEFINED

#include <gtk/gtk.h>
#include <string>
	using namespace std;
#include "GeckoEmbed.h"

class AppWindow {

	private:
		
		void setupCallbacks(); 

		static void eventDestroy(GtkWidget* widget, gpointer data); 

		GtkWidget* window;
		GeckoEmbed gecko;

	public:

		AppWindow(int argc, char* argv[]); 
		
		~AppWindow(); 

		void setContent(GtkWidget* gtkWidget); 

		void show(); 

		void setTitle(string newTitle); 

		void start(); 
};

#endif

