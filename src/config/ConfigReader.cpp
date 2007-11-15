#include <sstream>
	using std::stringstream;
#include <iostream>
	using std::cout;
	using std::endl;
#include "ConfigIO.h"

/**
 * Create a new ConfigReader object
 */
ConfigReader::ConfigReader() 
	: ConfigIO::ConfigIO() {
	this->errors = "";
}

/**
 * Process the contents of the config XML and set values into a given ConfigContainer
 *
 * @param config - the ConfigContainer object to populate
 *
 * @return true if the config was parsed successfully
 */
bool ConfigReader::appendConfigToContainer(ConfigContainer& config) {
	bool success = true;
	xmlDocPtr doc = getXmlDoc();
	xmlNodePtr groups;
	xmlNodePtr keys;
	xmlNodePtr root = doc->children;
	// The purpose of the "->next->next" is to ignore all "text" nodes
	for(groups = root->children->next; groups != NULL; groups = groups->next->next) {
		string groupName = (char*)groups->name;
		for(keys = groups->children->next; keys != NULL; keys = keys->next->next) {
			string keyName = (char*)keys->name;
			// Convert to a namespace config code
			string configCode = groupName + "_" + keyName;
			transform(configCode.begin(), configCode.end(), configCode.begin(), toupper);
			// Set the relevant ConfigContainer setting
			resolveConfigCode(configCode, config, groupName, keys);
		}
	}
	return success;
}

/**
 * Resolve the config code and save the value to the given ConfigContainer
 *
 * @param configCode - config code to resolve
 * @param config - the active config container
 * @param groupName - the name of the current key group
 * @param key - the XML content of the key
 */
void ConfigReader::resolveConfigCode(string configCode, ConfigContainer &config, string groupName, xmlNodePtr &key) {
	string keyName = (char*)key->name;
	string keyValue = (char*)xmlNodeGetContent(key);
	if (configCode == "APPLICATION_URL") { config.setAppUrl(keyValue); }
	else if (configCode == "APPLICATION_TITLE") { config.setAppTitle(keyValue); }
	else if (configCode == "APPLICATION_WINDOWGEOMETRY") { config.setWindowGeom(convertToGeometry(key)); }
	else if (configCode == "DOMAINS_DEFAULT") { config.setDomainDefault(keyValue); }
	else if (configCode == "DOMAINS_DROPADVERTS") { config.setAdvertsHidden(convertToBoolean(keyValue)); }
	else if (configCode == "DOMAINS_RULES") { config.appendDomainRules(convertToGroupedVector(key)); }
	else {
		this->errors += ("<" + groupName + "><" + keyName + ">" + " is not a recognised key\n");
	}
}

/**
 * Cast a string setting into an int
 *
 * @param strIn - the string to parse
 *
 * @return the integer value, or throw an error if parse failed
 */
int ConfigReader::convertToInt(string strIn) {
	stringstream ss(strIn);
	int intOut = 0;
	ss >> intOut;
	if (ss.fail()) {
		this->errors += (strIn + " is not a number\n");
	}
	return intOut;
}

/**
 * Cast a string setting into an boolean
 *
 * @param strIn - the string to parse
 *
 * @return the boolean value
 */
bool ConfigReader::convertToBoolean(string strIn) {
	return (strIn == "true");
}

/**
 * Cast the children of an XML element to a vector<string>
 *
 * @param xmlList - pointer to the node to parse
 * @param elementName - process elements that have this name
 *
 * @return the vector of items
 */
vector<string> ConfigReader::convertToVector(const xmlNodePtr& xmlList, string elementName) {
	vector<string> out;
	xmlNodePtr entries;
	for(entries = xmlList->children->next; entries != NULL; entries = entries->next->next) {
		string entryNameCheck = (char*)entries->name;
		if (entryNameCheck == elementName) {
			string entryValue = (char*)xmlNodeGetContent(entries);
			out.push_back(entryValue);
		}
	}
	return out;
}

/**
 * Cast the children of an XML element to a 2D vector<string> (group->value)
 *
 * @param xmlList - pointer to the node to parse
 *
 * @return the vector of items (key = group->value)
 */
vector<Rule> ConfigReader::convertToGroupedVector(const xmlNodePtr& xmlList) {
	vector<Rule> out;
	xmlNodePtr entries;
	for(entries = xmlList->children->next; entries != NULL; entries = entries->next->next) {
		string group = (char*)entries->name;
		string entryValue = (char*)xmlNodeGetContent(entries);
		Rule entry(group, entryValue);
		out.push_back(entry);
	}
	return out;
}

/**
 * Cast the children of an XML element to a Geometry
 *
 * @param xmlList - pointer to the node to parse
 *
 * @return the geometry shape
 */
Geometry ConfigReader::convertToGeometry(const xmlNodePtr& xmlList) {
	xmlNodePtr entries;
	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;
	for(entries = xmlList->children->next; entries != NULL; entries = entries->next->next) {
		string dimension = (char*)entries->name;
		string value = (char*)xmlNodeGetContent(entries);
		if (dimension == "left") left = convertToInt(value);
		else if (dimension == "top") top = convertToInt(value);
		else if (dimension == "width") width = convertToInt(value);
		else if (dimension == "height") height = convertToInt(value);
		else {
			cout << "geometry part " << dimension << " not understood" << endl;
		}
	}
	Geometry out(left, top, width, height);
	return out;
}

