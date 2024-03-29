#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "AppWindow.h"
#include "ConfigIO.h"

namespace fs = boost::filesystem;

/**
 * Create the application window
 *
 * @param argc - number of arguments passed into main()
 * @param argv[] - the arguments passed into main()
 * @param config - the application configuration settings
 */
AppWindow::AppWindow(int argc, char *argv[], ConfigContainer config) {
	menuBar = NULL;
	statusBar = NULL;
	gtk_set_locale();
	std::cout << "locale set" << std::endl;
	gtk_init(&argc, &argv);
	std::cout << "gtk init() called" << std::endl;
	window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	windowContainer = gtk_vbox_new(false, 0);

	// Set up the global keyboard accelerator interface
	accelGroup = gtk_accel_group_new();

	// Set up the window
	setConfig(config);
	Geometry geom = config.getWindowGeom();
	gtk_window_move(window, geom.getLeft(), geom.getTop());
	posEventFirstPass = true; 
	gtk_window_set_default_size(window, geom.getWidth(), geom.getHeight());
	setTitle(config.getAppTitle());
	string iconPath = config.getAppIcon();
	if (fs::is_regular(fs::path(iconPath))) {
		// Set the icon, if it exists
		setIcon(iconPath);
	}
	else {
		cout << "could not load icon, file does not exist: " << iconPath << endl;
	}
	// Attach the menu bar
	if (config.hasMenuBar() == true) {
		menuBar = new MenuBar(config.getMenuBar(), &gecko, accelGroup);
		setContent(menuBar->getMenuWidget(), false);
	}

	// Attach the Gecko engine
	gecko.init(config);
	setContent(gecko.getFrame(), true);

	// Attach the status bar
	if (config.hasStatusBar() == true) {
		statusBar = new StatusBar();
		setContent(statusBar->getWidget(), false);
		gecko.attachStatusBar(statusBar);
	}

	// Set up window callback events
	setupCallbacks();

	gtk_window_add_accel_group(window, accelGroup);
}

/**
 * Destroy the application window
 */
AppWindow::~AppWindow() {
	gecko.tearDown();
	if (menuBar != NULL) delete menuBar;
	if (statusBar != NULL) delete statusBar;
}

/**
 * Attach a GtkWidget to this window
 *
 * @param gtkWidget - the widget to place on the window
 * @param stretch - if this is true, the widget is stretched to fill remaining space on the window
 */
void AppWindow::setContent(GtkWidget* gtkWidget, bool stretch) {
	gtk_box_pack_start(GTK_BOX(windowContainer), gtkWidget, stretch, stretch, 0);
}

/**
 * Show the application window
 */
void AppWindow::show() {
	// Add the parent container to the window
	gtk_container_add(GTK_CONTAINER(window), windowContainer);
	gtk_widget_show_all(GTK_WIDGET(window));
}

/**
 * Change the title on the window
 *
 * @param newTitle - the new title to display
 */
void AppWindow::setTitle(string newTitle) {
	gtk_window_set_title(window, newTitle.c_str());
}

/**
 * Change the application icon
 *
 * @param path - local path to icon image
 */
void AppWindow::setIcon(string path) {
	if (path != "")
		gtk_window_set_icon_from_file(window, path.c_str(), NULL);
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
	// Add new signal events here
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(eventDestroy), this);
	g_signal_connect(G_OBJECT(window), "configure-event", G_CALLBACK(eventWindowProperty), this);
}

/**
 * Triggered when a window has been destroyed (handled internally by an event)
 *
 * @param *window - reference to the window object
 * @param parent - the owner of this callback
 */
void AppWindow::eventDestroy(GtkWindow *window, AppWindow& parent) {
	// Save window geometry to user session on exit
	ConfigContainer *config = parent.getConfig();
	ConfigWriter writer;
	writer.loadFile(config->getSaveToConfig());
	writer.saveWindowGeometry(config);
	gtk_main_quit();
}

/**
 * Triggered when window has moved or resized (handled internally by an event)
 *
 * @param *window - reference to the window object
 * @param *event - event object returned by GDK layer
 * @param parent - the owner of this callback
 *
 * @return always false
 */
bool AppWindow::eventWindowProperty(GtkWindow *window, GdkEventConfigure* event, AppWindow& parent) {
	if (parent.posEventFirstPass) {
		// Get original coords
		Geometry geom = parent.getConfig()->getWindowGeom();
		// Correct the position on first pass
		gtk_window_move(window, geom.getLeft(), geom.getTop());
		parent.posEventFirstPass = false;
	}
	// Retrieve the new window size
	ConfigContainer *config = parent.getConfig();
	Geometry geom(event->x, event->y, event->width, event->height);
	config->setWindowGeom(geom);
	// Always return false, otherwise the event may not trigger properly (GTK will cancel, but Xorg will honour it)
	return false;
}

