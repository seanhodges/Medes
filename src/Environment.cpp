#include <stdlib.h>
#include "Environment.h"

/**
 * Collect the environment information
 */
Environment::Environment() {
	this->userHomePath = getenv("HOME");
}

