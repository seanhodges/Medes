#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include "AppWindow.h"
#include "ConfigContainer.h"
#include "ConfigReader.h"

void printUsage() {
	cout << "medes 0.1" << endl;
	cout << "Usage: medes [config file]" << endl;
	cout << endl;
}

int main(int argc, char* argv[]) {

	// Set MOZILLA_FIVE_HOME for gtkmozembed to work
	setenv("MOZILLA_FIVE_HOME", "/usr/lib/firefox", 0);

	// Read the arguments passed in
	string targetAppXML;
	if (argc > 1) {
		targetAppXML = (string)argv[1];
	}
	else {
		printUsage();
		return 1;
	}

	// Load the application configuration
	ConfigContainer config;
	ConfigReader reader;
	bool loaded = reader.loadFile(targetAppXML);
	if (loaded) {
		reader.appendConfigToContainer(config);		
	}
	else {
		cout << "Error: could not read config file: " + targetAppXML << endl;
		printUsage();
		return 1;
	}

	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

