#ifndef ENVIRONMENT_DEFINED
#define ENVIRONMENT_DEFINED

#include <string>
	using std::string;
#include "Native.h"

class Environment {

	private:

		string userHomePath;

	public:

		Environment();

		// User profile path
		string getUserProfilePath() { return userHomePath + "/.medes/"; }

		// XML config files
		string getGlobalXMLPath() { return (string)APP_RESOURCE_PATH + "/global.xml"; }
		string getAdvertXMLPath() { return (string)APP_RESOURCE_PATH + "/adverts.xml"; }
		string getGlobalWebAppPath() { return (string)APP_RESOURCE_PATH + "/webapps/"; }
		string getUserWebAppPath() { return getUserProfilePath() + "webapps/"; }
		string getUserGeckoProfilePath() { return getUserProfilePath() + "mozilla/"; }

};

#endif
