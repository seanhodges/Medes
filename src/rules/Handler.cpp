#include <deque>
	using std::deque;
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
		GroupedEntry rule = *it;
		if (ruleMatches(rule, target)) {
			execRule(rule, target);
			ruleFound = true;
			// Break after first rule found
			break;
		}
	}
	if (!ruleFound) {
		cout << "no rule applied to target, using default rule for: " + target << endl;
		// Run the default rule on this target
		GroupedEntry defaultRuleObject(this->defaultRule, target);
		execRule(defaultRuleObject, target);
	}
	return ruleFound;
}

