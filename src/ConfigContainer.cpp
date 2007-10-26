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
	vector<string> domainList;
	domainList.push_back("about:blank");
	setDomainList(domainList);
}

/**
 * Add a new domain to the list
 *
 * @param newEntry - the URL to add
 */
void ConfigContainer::appendDomainList(string newEntry) {
	getDomainList().push_back(newEntry);
}

/**
 * Construct a grouped vector object
 *
 * @param group - a group entity
 * @param value - a value for an entry in the given group
 */
GroupedVector::GroupedVector(string group, string value) {
	this->group = group;
	this->value = value;
}

