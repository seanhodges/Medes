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
		if (scheme == "http") targetType = TargetHandler::REMOTE;
		else if (scheme == "https") targetType = TargetHandler::REMOTE;
		else if (scheme == "ftp") targetType = TargetHandler::REMOTE;
		else if (scheme == "file") targetType = TargetHandler::LOCAL;
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
		case TargetHandler::REMOTE:
			cout << "target is remote" << endl;
			doGecko();
			break;
		case TargetHandler::LOCAL:
			cout << "target is local" << endl;
			doGecko();
			break;
		case TargetHandler::JAVASCRIPT:
			cout << "target is javascript" << endl;
			doGecko();
			break;
		case TargetHandler::COMMAND:
			cout << "target is a command" << endl;
			doCommand();
			break;
		default:
			cout << "internal targethandler error, no action assigned for " << target << endl;
	}
}

/**
 * Perform an HTTP action
 */
void TargetHandler::doGecko() {
	gecko->setUrl(target);
}

/**
 * Execute a Medes command
 */
void TargetHandler::doCommand() {
	// Commands are currently not implemented, assume "quit"
	// TODO: Implement the command handling
	exit(0);
}

