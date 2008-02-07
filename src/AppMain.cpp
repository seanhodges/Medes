#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "Environment.h"
#include "AppWindow.h"
#include "ConfigContainer.h"
#include "ConfigIO.h"

namespace fs = boost::filesystem;

void printUsage() {
	cout << "medes 0.1.0" << endl;
	cout << "Usage: medes [webapp name]" << endl;
	cout << endl;
}

vector<string> getTargetConfigs(string targetAppXML) {
	Environment env;
	// Load the config files in this order
	vector<string> targetConfig;
	targetConfig.push_back(env.getGlobalXMLPath());
	targetConfig.push_back(env.getAdvertXMLPath());
	targetConfig.push_back(env.getGlobalWebAppPath() + targetAppXML);
	targetConfig.push_back(env.getUserWebAppPath() + targetAppXML);
	return targetConfig;
}

int main(int argc, char* argv[]) {

	Environment env;

	// Set MOZILLA_FIVE_HOME for gtkmozembed to work
	setenv("MOZILLA_FIVE_HOME", MOZILLA_FIVE_HOME, 0);

	// Build the user profile if it doesnt exist yet
	cout << "checking for user profile" << endl;
	fs::path profilePath = fs::system_complete(fs::path(env.getUserProfilePath(), fs::native));
	if (!fs::exists(profilePath)) {
		cout << "user profile directory does not exist, creating a new one" << endl;
		int profileCreated = fs::create_directory(profilePath);
		// Build the profile, stopping if something fails to create/copy
		if (profileCreated) profileCreated = fs::create_directory(fs::system_complete(fs::path(env.getUserGeckoProfilePath(), fs::native)));
		if (profileCreated) profileCreated = fs::create_directory(fs::system_complete(fs::path(env.getUserWebAppPath(), fs::native)));
		if (profileCreated) {
			cout << "new profile has been created" << endl;
		}
		else {
			cout << "error: could not create new profile" << endl;
			return 1;
		}
	}

	// Read the arguments passed in
	string targetAppXML;
	if (argc > 1) {
		targetAppXML = (string)argv[1] + ".xml";
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
		string status = "";
		string errors = "";
		bool loaded = reader.loadFile(*it);
		if (loaded) {
			// Parse the config file, if it loaded successfully
			bool success = reader.appendConfigToContainer(config);
			errors = reader.getParseErrors();
			if (success) {
				if (errors == "") status = " success";
				else status = " completed with errors (see below)";
			}
			else status = " failed";
		}
		else {
			status = " not found";
		}
		cout << status << endl;
		if (errors != "") {
			// Display any reported parse errors
			cout << errors;
		}
	}
	// User session is saved to last opened config file
	if ((int)targetConfig.size() > 0)
		config.setSaveToConfig(targetConfig.back());

    cout << "Creating appwindow" << std::endl;
	// Create the application window
	AppWindow appWindow(argc, argv, config);
	appWindow.show();
	appWindow.start();

    return 0;
}

