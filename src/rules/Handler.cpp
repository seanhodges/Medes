#include "RuleHandlers.h"

/**
 * Initialise the handler
 */
Handler::Handler(ConfigContainer config) {
	this->config = config;
}

/**
 * Run the rules against a target
 *
 * @param target - a target string to match
 */
bool Handler::runRules(string target) { 
	return false;
}

/**
 * Callback event for page redirection
 *
 * @param embed - the mozilla object
 * @param uri - the new URL passed to the engine
 * @param parent - the parent instance for this callback
 *
 * @return true to stop redirection event, otherwise false
 */
/*gint GeckoEmbed::open_uri_cb(GtkMozEmbed *embed, const char *uri, GeckoEmbed& parent) {
	bool ruleFound = false;
	bool cancelRedirect = true;
	string target = uri;
	deque<GroupedEntry> domainRules = parent.getConfig().getDomainRules();
	for (deque<GroupedEntry>::iterator it = domainRules.begin(); it != domainRules.end(); it++) {
		GroupedEntry entry = *it;
		if (target.find(entry.getValue()) == 0) {
			// A target rule has been found (break after valid rule)
			if (entry.getGroup() == "internal") {
				cout << "page redirection to: " + target << endl;
				cancelRedirect = false;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "external") {
				cout << "executing handler for domain: " + target << endl;
				string cmd = "gnome-www-browser " + target;
				system(cmd.c_str());
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "advert") {
				cout << "dropping advert: " + target << endl;
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else if (entry.getGroup() == "drop") {
				cout << "dropping domain target: " + target << endl;
				cancelRedirect = true;
				ruleFound = true;
				break;
			}
			else {
				cout << "(!!!) ignoring unknown target rule: " + entry.getGroup() << endl;
			}
		}
	}
	if (!ruleFound) {
		cout << "(!!!) no rule set for target domain: " + target << endl;
	}
	return cancelRedirect;
}*/
