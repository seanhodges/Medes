#include "AppWindow.h"
#include "ConfigContainer.h"
#include "ConfigReader.h"

int main(int argc, char* argv[]) {

	// Load the application configuration
	ConfigContainer config;
	ConfigReader reader;
	reader.loadFile(argv[1]);
	reader.appendConfigToContainer(config);

	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

