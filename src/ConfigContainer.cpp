#include "ConfigContainer.h"

/**
 * Provide some sensible defaults for the application
 * These should be over-ridden by the config XML stack
 */
ConfigContainer::ConfigContainer() {
	setAppUrl("about:blank");
	setAppTitle("No application loaded");
	setAppWidth(800);
	setAppHeight(600);
	this->domainRules.push_front(new GroupedEntry("internal", "about:blank"));
}

/**
 * Append a set of domain rules to the top of the main domain rules list
 *
 * @param newRules - the rules to add
 */
void ConfigContainer::appendDomainRules(deque<GroupedEntry> newRules) {
	while(!newRules.empty()) {
		GroupedEntry newEntry = newRules.pop_back();
		this->domainRules.push_front(newEntry);
	}
}

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

