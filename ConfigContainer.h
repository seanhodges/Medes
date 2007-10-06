#ifndef CONFIGCONTAINER_DEFINED
#define CONFIGCONTAINER_DEFINED

#include <string>
	using std::string;

class ConfigContainer {

	private:
		
		string appUrl;
		string appTitle;
		int appWidth;
		int appHeight;

	public:

		ConfigContainer();

		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		int getAppWidth() { return appWidth; }
		int getAppHeight() { return appHeight; }

		void setAppUrl(string newValue) { appUrl = newValue; }
		void setAppTitle(string newValue) { appTitle = newValue; }
		void setAppWidth(int newValue) { appWidth = newValue; }
		void setAppHeight(int newValue) { appHeight = newValue; }

};

#endif
