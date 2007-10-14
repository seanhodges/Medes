#ifndef CONFIGCONTAINER_DEFINED
#define CONFIGCONTAINER_DEFINED

#include <string>
	using std::string;
#include <vector>
	using std::vector;

class ConfigContainer {

	private:
		
		string appUrl;
		string appTitle;
		int appWidth;
		int appHeight;
		vector<string> domainList;

	public:

		ConfigContainer();

		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		int getAppWidth() { return appWidth; }
		int getAppHeight() { return appHeight; }
		vector<string>& getDomainList() { return domainList; }

		void setAppUrl(const string &newValue) { appUrl = newValue; }
		void setAppTitle(const string &newValue) { appTitle = newValue; }

		void setDomainList(const vector<string>& newList) { 
			domainList = newList; 
		}

		void appendDomainList(string newEntry);

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
