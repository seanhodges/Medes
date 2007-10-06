#include "AppWindow.h"
#include "ConfigContainer.h"

int main(int argc, char* argv[]) {

	// Load the application configuration
	ConfigContainer config;

	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

