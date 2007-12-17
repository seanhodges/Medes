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
		string accel;
		bool separator;

	public:

		MenuElement() {};
		MenuElement(string label, string group, string condition, string target, string accel, bool isSeparator);
		
		string getLabel() { return this->label; }
		string getGroup() { return this->group; }
		string getCondition() { return this->condition; }
		string getTarget() { return this->target; }
		string getAccel() { return this->accel; }
		bool isSeparator() { return this->separator; }
};

class ConfigContainer {

	private:
		
		// Target save path for ConfigWriter
		string saveToConfig;

		// Application
		string appUrl;
		string appTitle;
		string appIcon;
		Geometry windowGeom;

		// Rules
		string httpDefaultRule;
		deque<Rule> httpRules;
		string javascriptDefaultRule;
		deque<Rule> javascriptRules;
		bool hideAdverts;

		// Interface
		bool menuBarEnabled;
		bool statusBarEnabled;
		vector<MenuElement> menuBar;
		vector<MenuElement> contextMenu;

	public:

		ConfigContainer();

		string getSaveToConfig() { return saveToConfig; }
		string getAppUrl() { return appUrl; }
		string getAppTitle() { return appTitle; }
		string getAppIcon() { return appIcon; }
		Geometry getWindowGeom() { return windowGeom; }
		string getHttpDefaultRule() { return httpDefaultRule; }
		string getJavascriptDefaultRule() { return javascriptDefaultRule; }
		bool isAdvertsHidden() { return hideAdverts; }
		deque<Rule>& getHttpRules() { return httpRules; }
		deque<Rule>& getJavascriptRules() { return javascriptRules; }
		vector<MenuElement>& getMenuBar() { return menuBar; }
		vector<MenuElement>& getContextMenu() { return contextMenu; }

		void setSaveToConfig(string saveToConfig) { this->saveToConfig = saveToConfig; }
		void setAppUrl(string appUrl) { this->appUrl = appUrl; }
		void setAppTitle(string appTitle) { this->appTitle = appTitle; }
		void setAppIcon(string appIcon);
		void setWindowGeom(Geometry windowGeom) { this->windowGeom = windowGeom; }
		void setHttpDefaultRule(string httpDefaultRule) { this->httpDefaultRule = httpDefaultRule; }
		void setJavascriptDefaultRule(string javascriptDefaultRule) { this->javascriptDefaultRule = javascriptDefaultRule; }
		void setAdvertsHidden(bool hideAdverts) { this->hideAdverts = hideAdverts; }
		void setMenuBarEnabled(bool menuBarEnabled) { this->menuBarEnabled = menuBarEnabled; }
		void setStatusBarEnabled(bool statusBarEnabled) { this->statusBarEnabled = statusBarEnabled; }

		bool hasMenuBar() { return menuBarEnabled; }
		bool hasStatusBar() { return statusBarEnabled; }

		void replaceHttpRules(deque<Rule> newRules) { httpRules = newRules; }
		void appendHttpRules(vector<Rule> newRules);
		void appendHttpRules(Rule newRule);

		void replaceJavascriptRules(deque<Rule> newRules) { javascriptRules = newRules; }
		void appendJavascriptRules(vector<Rule> newRules);
		void appendJavascriptRules(Rule newRule);

		void replaceMenuBar(vector<MenuElement> newMenu) { menuBar = newMenu; }
		void appendMenuBar(vector<MenuElement> newMenu);
		void appendMenuBar(MenuElement newItem);

		void replaceContextMenu(vector<MenuElement> newMenu) { contextMenu = newMenu; }
		void appendContextMenu(vector<MenuElement> newMenu);
		void appendContextMenu(MenuElement newItem);
};

#endif
