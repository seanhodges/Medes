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

vector<string> getTargetConfigs(string targetAppXML) {
	// Load the config files in this order
	vector<string> targetConfig;
	targetConfig.push_back("/usr/local/share/medes/global.xml");
	targetConfig.push_back("/usr/local/share/medes/adverts.xml");
	targetConfig.push_back("/usr/local/share/medes/webapps/" + targetAppXML);
	targetConfig.push_back("~/.medes/webapps/" + targetAppXML);
	return targetConfig;
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

	// Load the configuration files
	vector<string> targetConfig = getTargetConfigs(targetAppXML);
	ConfigContainer config;
	ConfigReader reader;
	for (vector<string>::iterator it = targetConfig.begin(); it != targetConfig.end(); it++) {
		cout << "loading " + *it + "...";
		bool loaded = reader.loadFile(*it);
		if (loaded) {
			cout << " success";
			reader.appendConfigToContainer(config);		
		}
		else {
			cout << " not found";
		}
		cout << endl;
	}

	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

