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

		void setAppWidth(int newValue) { 
			// Constrain the min width
			if (newValue > 100) 
				appWidth = newValue; 
		}

		void setAppHeight(int newValue) { 
			// Constrain the min height
			if (newValue > 100) 
				appHeight = newValue; 
		}

};

#endif
