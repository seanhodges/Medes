#include "ConfigContainer.h"

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
 * Provide some sensible defaults for the application
 * These should be over-ridden by the config XML stack
 */
ConfigContainer::ConfigContainer() {
	setAppUrl("about:blank");
	setAppTitle("No application loaded");
	Geometry geom(0, 0, 640, 480);
	setWindowGeom(geom);
	setDomainDefault("external");
	setAdvertsHidden(false);
	Rule defaultEntry("internal", "about:blank");
	this->domainRules.push_front(defaultEntry);
}

/**
 * Append a set of domain rules to the top of the main domain rules list
 *
 * @param newRules - the rules to add
 */
void ConfigContainer::appendDomainRules(vector<Rule> newRules) {
	while(!newRules.empty()) {
		Rule newEntry; 
		newEntry = (Rule)newRules.back();
		this->domainRules.push_front(newEntry);
		newRules.pop_back();
	}
}

/**
 * Append a single domain rule to the top of the main domain rules list
 *
 * @param newRules - the rule to add
 */
void ConfigContainer::appendDomainRules(Rule newRule) {
	Rule newEntry; 
	this->domainRules.push_front(newRule);
}

