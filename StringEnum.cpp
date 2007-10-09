#include "StringEnum.h"

StringEnum::StringEnum() {
	enumIndex = 0;
}

/**
 * Declare an enumerator constant
 *
 * @param identifier - a human-readable identifier for this enum value
 */
void StringEnum::declare(string identifier) {
	enumArray[identifier] = enumIndex++;
}

/**
 * Resolve (and return) an enumerator constant
 *
 * @param identifier - a human-readable identifier for this enum value
 *
 * @return the enum value
 */
int StringEnum::resolve(string identifier) {
	return enumArray[identifier];
}

