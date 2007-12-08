#ifndef APPWINDOW_DEFINED
#define APPWINDOW_DEFINED

#include <gtk/gtk.h>
#include <string>
	using std::string;
#include "GeckoEmbed.h"
#include "ConfigContainer.h"
#include "MenuBar.h"

class AppWindow {

	private:

		void setupCallbacks();

		static void eventDestroy(GtkWindow *window, AppWindow &parent);
		static bool eventWindowProperty(GtkWindow *window, GdkEventConfigure* event, AppWindow &parent);

		ConfigContainer config;

		GtkWindow* window;
		GtkWidget* windowContainer;
		MenuBar* menuBar;
		GeckoEmbed gecko;

	public:

		AppWindow(int argc, char* argv[], ConfigContainer config);

		~AppWindow();

		ConfigContainer *getConfig() { return &config; }

		void setConfig(ConfigContainer &config) { this->config = config; }
		void setContent(GtkWidget *gtkWidget, bool stretch);
		void setTitle(string newTitle);

		void show();
		void start();
};

#endif

