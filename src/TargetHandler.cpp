#include "TargetHandler.h"

/**
 * Start a handler on a specified target
 *
 * @param target - the target to evaluate
 * @param gecko - the running gecko instance
 */
TargetHandler::TargetHandler(string target, GeckoEmbed *gecko) {
	this->gecko = gecko;
	this->target = target;
	// Determine the target type from the URI scheme
	int endOfScheme = target.find(":");
	if (endOfScheme > 0) {
		string scheme = target.substr(0, endOfScheme);
		if (scheme == "http") targetType = TargetHandler::HTTP;
		else if (scheme == "https") targetType = TargetHandler::HTTP;
		else if (scheme == "ftp") targetType = TargetHandler::HTTP;
		else if (scheme == "javascript") targetType = TargetHandler::JAVASCRIPT;
		else if (scheme == "medes") targetType = TargetHandler::COMMAND;
		else {
			cout << "could not resolve target, the scheme " << scheme << " is not known" << endl;
			targetType = TargetHandler::UNKNOWN;
		}
	}
	else {
		cout << "could not resolve target, does not have a valid scheme prefix" << endl;
	}
}

/**
 * Execute the action for this target
 */
void TargetHandler::runAction() {
	switch (targetType) {
		case TargetHandler::HTTP:
			doHttp();
			break;
		case TargetHandler::JAVASCRIPT:
			doJavascript();
			break;
		case TargetHandler::COMMAND:
			doCommand();
			break;
		default:
			cout << "internal targethandler error, no action assigned for " << target << endl;
	}

}

/**
 * Perform an HTTP action
 */
void TargetHandler::doHttp() {
	cout << "target is http" << endl;
	gecko->setUrl(target);
}

/**
 * Perform a javascript action
 */
void TargetHandler::doJavascript() {
	cout << "target is javascript" << endl;
	gecko->setUrl(target);
}

/**
 * Execute a Medes command
 */
void TargetHandler::doCommand() {
	cout << "target is a command" << endl;
	// Commands are currently not implemented, assume "quit"
	// TODO: Implement the command handling
	exit(0);
}

