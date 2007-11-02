#ifndef ENVIRONMENT_DEFINED
#define ENVIRONMENT_DEFINED

#include <string>
	using std::string;
#include <Native.h>

class Environment {

	private:

		string userHomePath;

	public:
		
		Environment();

		// XML config files
		string getSystemGlobalXMLPath() { return APP_RESOURCE_PATH; }
		string getSystemAdvertXMLPath() { return APP_RESOURCE_PATH; }
		string getSystemWebAppXMLPath() { return (string)APP_RESOURCE_PATH + "webapps/"; }
		string getUserWebAppXMLPath() { return userHomePath + "webapps/"; }

		// Location for Gecko profile
		string getUserProfilePath() { return userHomePath; }

};

#endif
