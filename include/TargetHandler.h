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

		enum TargetType {REMOTE, LOCAL, JAVASCRIPT, COMMAND, UNKNOWN};

		TargetHandler(string target, GeckoEmbed *gecko);

		TargetType getTargetType() { return targetType; }
		void runAction();

	private:
		
		void doGecko();
		void doCommand();

		GeckoEmbed *gecko;
		string target;
		TargetType targetType;
};

#endif

