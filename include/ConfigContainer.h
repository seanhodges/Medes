#ifndef CONFIGCONTAINER_DEFINED
#define CONFIGCONTAINER_DEFINED

#include <string>
	using std::string;
#include <deque>
	using std::deque;

class GroupedEntry {

	private:

		string group;
		string value;

	public:
		
		GroupedEntry(string group, string value);

		string getGroup() { return group; }
		string getValue() { return value; }

};

class ConfigContainer {

	private:
		
		string appUrl;
		string appTitle;
		int appWidth;
		int appHeight;
		deque<GroupedEntry> domainRules;

	public:

		ConfigContainer();

		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		int getAppWidth() { return appWidth; }
		int getAppHeight() { return appHeight; }
		deque<GroupedEntry>& getDomainRules() { return domainRules; }

		void setAppUrl(const string &newValue) { appUrl = newValue; }
		void setAppTitle(const string &newValue) { appTitle = newValue; }

		void replaceDomainRules(const deque<GroupedEntry>& newRules) { 
			domainRules = newRules; 
		}

		void appendDomainRules(deque<GroupedEntry> newRules);

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
