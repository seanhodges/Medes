#include "ConfigContainer.h"
#include "Environment.h"

/**
 * Construct a rule pod
 *
 * @param group - a group entity
 * @param value - a value for an entry in the given group
 */
Rule::Rule(string group, string value) {
	this->group = group;
	this->value = value;
}

/**
 * Construct a geometry pod
 *
 * @param left - left position of object
 * @param top - top position of object
 * @param width - width of object
 * @param height - height of object
 */
Geometry::Geometry(int left, int top, int width, int height) {
	this->left = left;
	this->top = top;
	if (width > 100) this->width = width; 
	if (height > 100) this->height = height; 
}

/**
 * Construct a menu element pod
 *
 * @param label - caption for menu element
 * @param group - name of menu section this element will be grouped in
 * @param condition - only show/enable this element if the condition returns true (ignored if "")
 * @param target - target URL action for this menu element
 * @param isSeparator - if true, this element is a menu separator
 */
MenuElement::MenuElement(string label, string group, string condition, string target, string accel, bool isSeparator) {
	this->label = label;
	this->group = group;
	this->condition = condition;
	this->target = target;
	this->accel = accel;
	this->separator = isSeparator;
}

/**
 * Provide some sensible defaults for the application
 * These should be over-ridden by the config XML stack
 */
ConfigContainer::ConfigContainer() {
	setSaveToConfig("save.xml");
	setAppUrl("about:blank");
	setAppTitle("No application loaded");
	setAppIcon("");
	Geometry geom(0, 0, 640, 480);
	setWindowGeom(geom);
	setHttpDefaultRule("external");
	setJavascriptDefaultRule("allow");
	setAdvertsHidden(false);
	// Add about:blank as allowed, in case something else screws up
	Rule defaultHttpEntry("internal", "about:blank");
	httpRules.push_front(defaultHttpEntry);
	setMenuBarEnabled(false);
	setStatusBarEnabled(true);
}

/**
 * Set the application icon relative to the icon store
 *
 * @param appIcon - the relative path to the icon image
 */
void ConfigContainer::setAppIcon(string appIcon) { 
	Environment env;
	this->appIcon = env.getIconStorePath() + appIcon;
}

/**
 * Append a set of domain rules to the top of the main domain rules list
 *
 * @param newRules - the rules to add
 */
void ConfigContainer::appendHttpRules(vector<Rule> newRules) {
	while(!newRules.empty()) {
		Rule newEntry = (Rule)newRules.back();
		httpRules.push_front(newEntry);
		newRules.pop_back();
	}
}

/**
 * Append a single domain rule to the top of the main domain rules list
 *
 * @param newRules - the rule to add
 */
void ConfigContainer::appendHttpRules(Rule newRule) {
	httpRules.push_front(newRule);
}

/**
 * Append a set of js rules to the top of the main js rules list
 *
 * @param newRules - the rules to add
 */
void ConfigContainer::appendJavascriptRules(vector<Rule> newRules) {
	while(!newRules.empty()) {
		Rule newEntry = (Rule)newRules.back();
		javascriptRules.push_front(newEntry);
		newRules.pop_back();
	}
}

/**
 * Append a single js rule to the top of the main js rules list
 *
 * @param newRules - the rule to add
 */
void ConfigContainer::appendJavascriptRules(Rule newRule) {
	javascriptRules.push_front(newRule);
}

/**
 * Append a set of menu items to the menu bar
 *
 * @param newItems - the menu items to add
 */
void ConfigContainer::appendMenuBar(vector<MenuElement> newItems) {
	while(!newItems.empty()) {
		MenuElement newItem = (MenuElement)newItems.back();
		menuBar.push_back(newItem);
		newItems.pop_back();
	}
}

/**
 * Append a single menu item to the menu bar
 *
 * @param newItem - the menu item to add
 */
void ConfigContainer::appendMenuBar(MenuElement newItem) {
	menuBar.push_back(newItem);
}

/**
 * Append a set of menu items to the context menu 
 * 
 * @param newItems - the menu items to add
 */
void ConfigContainer::appendContextMenu(vector<MenuElement> newItems) {
	while(!newItems.empty()) {
		MenuElement newItem = (MenuElement)newItems.back();
		contextMenu.push_back(newItem);
		newItems.pop_back();
	}
}

/**
 * Append a single menu item to the context menu 
 *
 * @param newItem - the menu item to add
 */
void ConfigContainer::appendContextMenu(MenuElement newItem) {
	contextMenu.push_back(newItem);
}

