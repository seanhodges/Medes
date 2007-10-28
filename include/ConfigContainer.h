#ifndef CONFIGCONTAINER_DEFINED
#define CONFIGCONTAINER_DEFINED

#include <string>
	using std::string;
#include <deque>
	using std::deque;
#include <vector>
	using std::vector;

class GroupedEntry {

	private:

		string group;
		string value;

	public:
		
		GroupedEntry() {};
		GroupedEntry(string group, string value);

		string getGroup() { return group; }
		string getValue() { return value; }

};

class ConfigContainer {

	private:
		
		// Application
		string appUrl;
		string appTitle;
		int appWidth;
		int appHeight;

		// Rules
		string domainDefault;
		bool hideAdverts;
		deque<GroupedEntry> domainRules;

	public:

		ConfigContainer();

		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		int getAppWidth() { return appWidth; }
		int getAppHeight() { return appHeight; }
		string getDomainDefault() { return domainDefault; }
		bool isAdvertsHidden() { return hideAdverts; }
		deque<GroupedEntry>& getDomainRules() { return domainRules; }

		void setAppUrl(const string& appUrl) { this->appUrl = appUrl; }
		void setAppTitle(const string& appTitle) { this->appTitle = appTitle; }
		void setAppWidth(int appWidth) { 
			// Constrain the min width
			if (appWidth > 100) 
				this->appWidth = appWidth; 
		}
		void setAppHeight(int appHeight) { 
			// Constrain the min height
			if (appHeight > 100) 
				this->appHeight = appHeight; 
		}
		void setDomainDefault(string domainDefault) { this->domainDefault = domainDefault; }
		void setAdvertsHidden(bool hideAdverts) { this->hideAdverts = hideAdverts; }
		void replaceDomainRules(deque<GroupedEntry> newRules) { 
			domainRules = newRules; 
		}
		void appendDomainRules(vector<GroupedEntry> newRules);
		void appendDomainRules(GroupedEntry newRule);

};

#endif
