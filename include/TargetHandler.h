#ifndef TARGETHANDLER_DEFINED
#define TARGETHANDLER_DEFINED

#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include "GeckoEmbed.h"

class TargetHandler {

	public:

		enum TargetType {HTTP, JAVASCRIPT, COMMAND, UNKNOWN};

		TargetHandler(string target, GeckoEmbed *gecko);

		TargetType getTargetType() { return targetType; }
		void runAction();

	private:
		
		void doHttp();
		void doJavascript();
		void doCommand();

		GeckoEmbed *gecko;
		string target;
		TargetType targetType;
};

#endif

