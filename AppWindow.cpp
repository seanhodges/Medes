#include "AppWindow.h"

/*
 * Create the application window
 *
 * @param argc - number of arguments passed into main()
 * @param argv[] - the arguments passed into main()
 */
AppWindow::AppWindow(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// Set up the window
	string configTitle = "Facebook";
	int configWidth = 800;
	int configHeight = 600;
	gtk_window_set_default_size(GTK_WINDOW(window), configWidth, configHeight);
	setTitle(configTitle);
	// Attach the Gecko engine
	gecko.init();
	AppWindow::setContent(gecko.getFrame());
	// Set up callback events
	setupCallbacks();
}

AppWindow::~AppWindow() {
	gecko.tearDown();
}

/**
 * Attach a GtkWidget to this window
 */
void AppWindow::setContent(GtkWidget* gtkWidget) {
	gtk_container_add(GTK_CONTAINER(window), gtkWidget);
}

/*
 * Show the application window
 */
void AppWindow::show() {
	gtk_widget_show_all(window);
}

/*
 * Change the title on the window
 *
 * @param newTitle - the new title to display
 */
void AppWindow::setTitle(string newTitle) {
	gtk_window_set_title(GTK_WINDOW (window), newTitle.c_str());
}

/*
 * Run the gtk_main() loop (event handler)
 */
void AppWindow::start() {
	gecko.bringUp();
	gtk_main();
}

/*
 * Set-up the event callbacks handled in this window
 */
void AppWindow::setupCallbacks() {
	g_signal_connect(G_OBJECT (window), "destroy", G_CALLBACK(eventDestroy), NULL);
}

/*
 * Destroy this window (handled internally by an event)
 *
 * @param *widget - reference to the window object
 * @param data - unused data from glib
 */
void AppWindow::eventDestroy(GtkWidget* widget, gpointer data) {
	gtk_main_quit();
}

