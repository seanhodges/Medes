#include <libxml/tree.h>
#include <libxml/xpath.h> 
#include <sstream>
	using std::stringstream;
#include <iostream>
	using std::cout;
	using std::endl;
#include <fstream>
	using std::fstream;
#include "ConfigReader.h"

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
	// Causes a segmentation fault, think it's needed?
	//xmlFreeDoc(ConfigReader::getXmlDoc());
	xmlCleanupParser();
}

/**
 * Load the config XML
 */
bool ConfigReader::loadFile(string xmlPath) {
	fstream fin;
	fin.open(xmlPath.c_str());
	if(fin.is_open()) {
		setFilePath(xmlPath);
		setXmlDoc(xmlParseFile(xmlPath.c_str()));
		fin.close();
		return true;
	}
	return false;
}

/**
 * Process the contents of the config XML and set values into a given ConfigContainer
 *
 * @param config - the ConfigContainer object to populate
 */
void ConfigReader::appendConfigToContainer(ConfigContainer& config) {
	bool appNameSet = false;
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
			if (configCode == "APPLICATION_URL") { config.setAppUrl(keyValue); appNameSet = true; }
			else if (configCode == "APPLICATION_TITLE") { config.setAppTitle(keyValue); }
			else if (configCode == "APPLICATION_WINDOWWIDTH") { config.setAppWidth(convertToInt(keyValue)); }
			else if (configCode == "APPLICATION_WINDOWHEIGHT") { config.setAppHeight(convertToInt(keyValue)); }
			else if (configCode == "DOMAINS_DEFAULT") { config.setDomainDefault(keyValue); }
			else if (configCode == "DOMAINS_DROPADVERTS") { config.setAdvertsHidden(convertToBoolean(keyValue)); }
			else if (configCode == "DOMAINS_RULES") { config.appendDomainRules(convertToGroupedVector(keys)); }
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
 * Cast a string setting into an boolean
 *
 * @param strIn - the string to parse
 *
 * @return the boolean value
 */
bool ConfigReader::convertToBoolean(string& strIn) {
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
 * Cast the children of an XML element to a loose-mapped vector (group->value)
 *
 * @param xmlList - pointer to the node to parse
 *
 * @return the vector of items (key = pair (group, value))
 */
vector<GroupedEntry> ConfigReader::convertToGroupedVector(const xmlNodePtr& xmlList) {
	vector<GroupedEntry> out;
	xmlNodePtr entries;
	for(entries = xmlList->children->next; entries != NULL; entries = entries->next->next) {
		string group = (char*)entries->name;
		string entryValue = (char*)xmlNodeGetContent(entries);
		GroupedEntry entry(group, entryValue);
		out.push_back(entry);
	}
	return out;
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

