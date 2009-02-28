#include <cstdlib>
	using std::system;
#include "Rules.h"

/**
 * Initialise the handler
 *
 * @param config - the config container containing the rules for this handler
 */
LocalRules::LocalRules(ConfigContainer config)
	: Rules::Rules(config.getLocalRules(), config.getLocalDefaultRule()) {
	allowRedirect = false;
}

/**
 * Check that a rule matches the target URL
 *
 * @param rule - the rule to interrogate
 * @param target - the target URL being matched
 *
 * @return true if a successful match was found
 */
bool LocalRules::ruleMatches(Rule rule, string target) { 
	// TODO: add some regex matching in the future
	if (target.find(rule.getValue()) == 0) {
		return true;
	}
	return false;
}

/**
 * Match and run a rule matching the given name
 *
 * @param rule - the rule to execute
 * @param target - the URL to execute
 */
void LocalRules::execRule(Rule rule, string target) {
	string ruleName = rule.getGroup();
	// Declare new domain rules here
	if (ruleName == "internal") { handleInternal(target); }
	else if (ruleName == "external") { handleExternal(target); }
	else if (ruleName == "drop") { handleDrop(target); }
	else { 
		cout << "(!!!) rule is not recognised and could not be applied: " + ruleName << endl; 
	}
}

/**
 * Action an internal domain rule
 *
 * @param target - the target URL
 */
void LocalRules::handleInternal(string target) {
	cout << "page redirection to: " + target << endl;
	allowRedirect = true;
}

/**
 * Action an external domain rule
 *
 * @param target - the target URL
 */
void LocalRules::handleExternal(string target) {
	cout << "executing handler for target: " + target << endl;
	string cmd = "gnome-www-browser " + target;
	system(cmd.c_str());
	allowRedirect = false;
}

/**
 * Action an drop domain rule
 *
 * @param target - the target URL
 */
void LocalRules::handleDrop(string target) {
	cout << "dropping local target: " + target << endl;
	allowRedirect = false;
}

