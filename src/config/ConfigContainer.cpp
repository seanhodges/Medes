#include "ConfigContainer.h"

/**
 * Construct a grouped object
 *
 * @param group - a group entity
 * @param value - a value for an entry in the given group
 */
GroupedEntry::GroupedEntry(string group, string value) {
	this->group = group;
	this->value = value;
}

/**
 * Provide some sensible defaults for the application
 * These should be over-ridden by the config XML stack
 */
ConfigContainer::ConfigContainer() {
	setAppUrl("about:blank");
	setAppTitle("No application loaded");
	setAppWidth(800);
	setAppHeight(600);
	setDomainDefault("external");
	setAdvertsHidden(false);
	GroupedEntry defaultEntry("internal", "about:blank");
	this->domainRules.push_front(defaultEntry);
}

/**
 * Append a set of domain rules to the top of the main domain rules list
 *
 * @param newRules - the rules to add
 */
void ConfigContainer::appendDomainRules(vector<GroupedEntry> newRules) {
	while(!newRules.empty()) {
		GroupedEntry newEntry; 
		newEntry = (GroupedEntry)newRules.back();
		this->domainRules.push_front(newEntry);
		newRules.pop_back();
	}
}

/**
 * Append a single domain rule to the top of the main domain rules list
 *
 * @param newRules - the rule to add
 */
void ConfigContainer::appendDomainRules(GroupedEntry newRule) {
	GroupedEntry newEntry; 
	this->domainRules.push_front(newRule);
}

