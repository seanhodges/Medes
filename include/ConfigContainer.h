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

class MenuElement {

	private:

		string label;
		string group;
		string condition;
		string target;

	public:

		MenuElement() {};
		MenuElement(string label, string group, string condition, string target);
		
		string getLabel() { return this->label; }
		string getGroup() { return this->group; }
		string getCondition() { return this->condition; }
		string getTarget() { return this->target; }

};

class ConfigContainer {

	private:
		
		// Target save path for ConfigWriter
		string saveToConfig;

		// Application
		string appUrl;
		string appTitle;
		Geometry windowGeom;

		// Rules
		string domainDefault;
		bool hideAdverts;
		deque<Rule> domainRules;

		// Interface
		vector<MenuElement> menuBar;
		vector<MenuElement> contextMenu;

	public:

		ConfigContainer();

		string getSaveToConfig() { return saveToConfig; }
		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		Geometry getWindowGeom() { return windowGeom; }
		string getDomainDefault() { return domainDefault; }
		bool isAdvertsHidden() { return hideAdverts; }
		deque<Rule>& getDomainRules() { return domainRules; }
		vector<MenuElement>& getMenuBar() { return menuBar; }
		vector<MenuElement>& getContextMenu() { return contextMenu; }

		void setSaveToConfig(string saveToConfig) { this->saveToConfig = saveToConfig; }
		void setAppUrl(string appUrl) { this->appUrl = appUrl; }
		void setAppTitle(string appTitle) { this->appTitle = appTitle; }
		void setWindowGeom(Geometry windowGeom) { this->windowGeom = windowGeom; }
		void setDomainDefault(string domainDefault) { this->domainDefault = domainDefault; }
		void setAdvertsHidden(bool hideAdverts) { this->hideAdverts = hideAdverts; }

		void replaceDomainRules(deque<Rule> newRules) { domainRules = newRules; }
		void appendDomainRules(vector<Rule> newRules);
		void appendDomainRules(Rule newRule);

		void replaceMenuBar(vector<MenuElement> newMenu) { menuBar = newMenu; }
		void appendMenuBar(vector<MenuElement> newMenu);
		void appendMenuBar(MenuElement newItem);

		void replaceContextMenu(vector<MenuElement> newMenu) { contextMenu = newMenu; }
		void appendContextMenu(vector<MenuElement> newMenu);
		void appendContextMenu(MenuElement newItem);
};

#endif
