#include "AppWindow.h"
#include "ConfigIO.h"

/**
 * Create the application window
 *
 * @param argc - number of arguments passed into main()
 * @param argv[] - the arguments passed into main()
 * @param config - the application configuration settings
 */
AppWindow::AppWindow(int argc, char *argv[], ConfigContainer config) {
	gtk_set_locale();
	gtk_init(&argc, &argv);
	window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	// Set up the window
	gtk_window_set_default_size(window, config.getAppWidth(), config.getAppHeight());
	setTitle(config.getAppTitle());
	// Attach the Gecko engine
	gecko.init(config);
	AppWindow::setContent(gecko.getFrame());
	// Set up callback events
	setupCallbacks();
}

/**
 * Destroy the application window
 */
AppWindow::~AppWindow() {
	gecko.tearDown();
}

/**
 * Attach a GtkWidget to this window
 */
void AppWindow::setContent(GtkWidget* gtkWidget) {
	gtk_container_add(GTK_CONTAINER(window), gtkWidget);
}

/**
 * Show the application window
 */
void AppWindow::show() {
	gtk_widget_show_all(GTK_WIDGET(window));
}

/**
 * Change the title on the window
 *
 * @param newTitle - the new title to display
 */
void AppWindow::setTitle(const string& newTitle) {
	gtk_window_set_title(window, newTitle.c_str());
}

/**
 * Run the gtk_main() loop (event handler)
 */
void AppWindow::start() {
	gecko.bringUp();
	gtk_main();
}

/**
 * Set-up the event callbacks handled in this window
 */
void AppWindow::setupCallbacks() {
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(eventDestroy), this);
}

/**
 * Destroy this window (handled internally by an event)
 *
 * @param *window - reference to the window object
 * @param parent - the owner of this callback
 */
void AppWindow::eventDestroy(GtkWindow* window, AppWindow& parent) {
	// Save window geometry to user config on exit
	ConfigContainer config = parent.getConfig();
	int width;
	int height;
	gtk_window_get_size(window, &width, &height);
	config.setAppWidth(width);
	config.setAppHeight(height);
	ConfigWriter writer;
	writer.saveWindowGeometry(config);
	gtk_main_quit();
}

