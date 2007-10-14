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

void ConfigContainer::appendDomainList(string newEntry) {
	getDomainList().push_back(newEntry);
}

