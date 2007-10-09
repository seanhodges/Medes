#include "ConfigReader.h"
#include <libxml/tree.h>
#include <libxml/xpath.h> 
#include <sstream>
	using std::stringstream;
#include <iostream>
	using std::cout;
	using std::endl;

/**
 * Initialise libxml
 */
ConfigReader::ConfigReader() {
	xmlInitParser();
	LIBXML_TEST_VERSION
}

/**
 * Shut down libxml
 */
ConfigReader::~ConfigReader() {
	xmlFreeDoc(ConfigReader::getXmlDoc());
	xmlCleanupParser();
}

/**
 * Load the config XML
 */
bool ConfigReader::loadFile(string xmlPath) {
	setFilePath(xmlPath);
	setXmlDoc(xmlParseFile(xmlPath.c_str()));
}

/**
 * Process the contents of the config XML and set values into a given ConfigContainer
 *
 * @param config - the ConfigContainer object to populate
 */
void ConfigReader::appendConfigToContainer(ConfigContainer& config) {
	xmlDocPtr doc = ConfigReader::getXmlDoc();
	xmlNodePtr groups;
	xmlNodePtr keys;
	xmlNodePtr root = doc->children;
	// The purpose of the "->next->next" is to ignore all "text" nodes
	for(groups = root->children->next; groups != NULL; groups = groups->next->next) {
		string groupName = (char*)groups->name;
		for(keys = groups->children->next; keys != NULL; keys = keys->next->next) {
			string keyName = (char*)keys->name;
			string keyValue = (char*)xmlNodeGetContent(keys);
			// Convert to a namespace config code
			string configCode = groupName + "_" + keyName;
			transform(configCode.begin(), configCode.end(), configCode.begin(), toupper);
			// Set the relevant ConfigContainer setting
			if (configCode == "APPLICATION_URL") { config.setAppUrl(keyValue); }
			else if (configCode == "APPLICATION_TITLE") { config.setAppTitle(keyValue); }
			else if (configCode == "APPLICATION_WINDOWWIDTH") { config.setAppWidth(convertToInt(keyValue)); }
			else if (configCode == "APPLICATION_WINDOWHEIGHT") { config.setAppHeight(convertToInt(keyValue)); }
			else {
				cout << "<" + groupName + "><" + keyName + ">" + " is not a recognised key" << endl;
			}
		}
	}
}

/**
 * Cast a string setting into an int
 *
 * @param strIn - the string to parse
 *
 * @return the integer value, or throw an error if parse failed
 */
int ConfigReader::convertToInt(string& strIn) {
	stringstream ss(strIn);
	int intOut = 0;
	ss >> intOut;
	if (ss.fail()) {
		cout << strIn + " is not a number" << endl;
	}
	return intOut;
}

/**
 * Return a setting
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to return
 * @return the setting value
 */
string ConfigReader::getSetting(string group, string key, string defaultValue) {
	string resultVal; 
	string query = "/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(ConfigReader::getXmlDoc());
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
	if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		resultVal = (char*)result->nodesetval->nodeTab[0]->content;
	}
	else {
		resultVal = defaultValue;
	}
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
	return resultVal;
}

/**
 * Modify a setting with a new value
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to change
 * @return the new setting value
 */
void ConfigReader::changeSetting(string group, string key, string newValue) {
	cout << "Changing application settings not yet implemented" << endl;
	string query = "/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(ConfigReader::getXmlDoc());
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
	if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		result->nodesetval->nodeTab[0]->content = (xmlChar*)newValue.c_str();
	}
	else {
		// TODO: Create new element
	}
	string filePath = ConfigReader::getFilePath();
	//xmlSaveFile((char*)filePath, ConfigReader::getXmlDoc());
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

