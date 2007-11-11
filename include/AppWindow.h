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

		static void eventDestroy(GtkWindow *window, AppWindow &parent); 
		static void eventResize(GtkWindow *window, AppWindow &parent); 

		ConfigContainer config;

		GtkWindow* window;
		GeckoEmbed gecko;

	public:

		AppWindow(int argc, char* argv[], ConfigContainer config); 
		
		~AppWindow(); 

		//ConfigContainer getConfig() { return config; }
		ConfigContainer *getConfig() { return &config; }

		void setConfig(ConfigContainer &config) { this->config = config; }
		void setContent(GtkWidget *gtkWidget); 
		void setTitle(string newTitle); 

		void show(); 
		void start(); 
};

#endif

