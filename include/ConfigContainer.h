#ifndef CONFIGCONTAINER_DEFINED
#define CONFIGCONTAINER_DEFINED

#include <string>
	using std::string;
#include <deque>
	using std::deque;
#include <vector>
	using std::vector;

class Rule {

	private:

		string group;
		string value;

	public:
		
		Rule() {};
		Rule(string group, string value);

		string getGroup() { return group; }
		string getValue() { return value; }

};

class Geometry {

	private:

		int top;
		int left;
		int width;
		int height;

	public:
		
		Geometry() {};
		Geometry(int left, int top, int width, int height);

		int getLeft() { return left; }
		int getTop() { return top; }
		int getWidth() { return width; }
		int getHeight() { return height; }

};

class ConfigContainer {

	private:
		
		// Application
		string appUrl;
		string appTitle;
		Geometry windowGeom;

		// Rules
		string domainDefault;
		bool hideAdverts;
		deque<Rule> domainRules;

	public:

		ConfigContainer();

		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		Geometry getWindowGeom() { return windowGeom; }
		string getDomainDefault() { return domainDefault; }
		bool isAdvertsHidden() { return hideAdverts; }
		deque<Rule>& getDomainRules() { return domainRules; }

		void setAppUrl(const string& appUrl) { this->appUrl = appUrl; }
		void setAppTitle(const string& appTitle) { this->appTitle = appTitle; }
		void setWindowGeom(Geometry windowGeom) { this->windowGeom = windowGeom; }
		void setDomainDefault(string domainDefault) { this->domainDefault = domainDefault; }
		void setAdvertsHidden(bool hideAdverts) { this->hideAdverts = hideAdverts; }
		void replaceDomainRules(deque<Rule> newRules) { domainRules = newRules; }
		void appendDomainRules(vector<Rule> newRules);
		void appendDomainRules(Rule newRule);

};

#endif
