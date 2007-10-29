#include <deque>
	using std::deque;
#include <iostream>
	using std::cout;
	using std::endl;
#include "RuleHandlers.h"

/**
 * Initialise the handler
 */
Handler::Handler(deque<GroupedEntry> ruleList, string defaultRule) {
	this->ruleList = ruleList;
	this->defaultRule = defaultRule;
}

/**
 * Run the rules against a target
 *
 * @param target - a target string to match
 */
bool Handler::runRules(string target) { 
	bool ruleFound = false;
	deque<GroupedEntry> ruleList = getRuleList();
	for (deque<GroupedEntry>::iterator it = ruleList.begin(); it != ruleList.end(); it++) {
		GroupedEntry entry = *it;
		if (hasRule(entry.getGroup())) {
			ruleFound = execRule(entry.getGroup(), entry.getValue());
			// Break after first rule found
			if (ruleFound) break;
		}
	}
	if (!ruleFound) {
		cout << "(!!!) no rule set for target: " + target << endl;
	}
	return ruleFound;
}

