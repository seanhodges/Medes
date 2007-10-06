#include "ConfigReader.h"

/**
 * Load the config XML
 */
ConfigReader::ConfigReader(string xmlPath) {
	// TODO
}

/**
 * Return a setting as a string
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to return
 * @return the setting value
 */
template<> string ConfigReader::getSetting<string>(string group, string key) {
	return ConfigResult(*this, group, key);
}

/**
 * Return a setting as an integer
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to return
 * @return the setting value
 */
template<> int ConfigReader::getSetting<int>(string group, string key) {
	return ConfigResult(*this, group, key);
}

/**
 * Return a setting as a boolean
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to return
 * @return the setting value
 */
template<> bool ConfigReader::getSetting<bool>(string group, string key) {
	return ConfigResult(*this, group, key);
}

