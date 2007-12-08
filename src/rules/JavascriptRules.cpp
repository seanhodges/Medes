#include "Rules.h"

/**
 * Initialise the handler
 *
 * @param config - the config container containing the rules for this handler
 */
JavascriptRules::JavascriptRules(ConfigContainer config)
	: Rules::Rules(config.getJavascriptRules(), config.getJavascriptDefaultRule()) {
	this->allowRedirect = false;
	this->dropAdverts = true;
}

/**
 * Check that a rule matches the target javascript action
 *
 * @param rule - the rule to interrogate
 * @param target - the target action being matched
 *
 * @return true if a successful match was found
 */
bool JavascriptRules::ruleMatches(Rule rule, string target) { 
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
 * @param target - the javascript action to execute
 */
void JavascriptRules::execRule(Rule rule, string target) {
	string ruleName = rule.getGroup();
	// Declare new domain rules here
	if (ruleName == "allow") { handleAllow(target); }
	else if (ruleName == "advert") { handleAdvert(target); }
	else if (ruleName == "drop") { handleDrop(target); }
	else { 
		cout << "(!!!) rule is not recognised and could not be applied: " + ruleName << endl; 
	}
}

/**
 * Action an allowed javascript rule
 *
 * @param target - the target action
 */
void JavascriptRules::handleAllow(string target) {
	cout << "executing javascript: " + target << endl;
	this->allowRedirect = true;
}

/**
 * Action a javascript-based advert 
 *
 * @param target - the target action
 */
void JavascriptRules::handleAdvert(string target) {
	if (this->dropAdverts) {
		cout << "dropping advert: " + target << endl;
		this->allowRedirect = false;
	}
	else {
		cout << "accepting advert: " + target << endl;
		this->allowRedirect = true;
	}
}

/**
 * Action to drop a javascript rule
 *
 * @param target - the target action
 */
void JavascriptRules::handleDrop(string target) {
	cout << "dropping javascript: " + target << endl;
	this->allowRedirect = false;
}

