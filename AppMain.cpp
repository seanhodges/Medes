#include "AppWindow.h"
#include "ConfigContainer.h"
#include "ConfigReader.h"

int main(int argc, char* argv[]) {

	// Load the application configuration
	ConfigContainer config;
	ConfigReader reader;
	bool loaded = reader.loadFile(argv[1]);
	if (loaded) {
		reader.appendConfigToContainer(config);		
	}

	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

