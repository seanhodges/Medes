#include "ConfigReader.h"
#include <libxml/tree.h>
#include <libxml/xpath.h> 
#include <sstream>
	using std::stringstream;

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
void ConfigReader::appendConfigToContainer(ConfigContainer config) {
	xmlDocPtr doc = ConfigReader::getXmlDoc();
	xmlNodePtr groups;
	xmlNodePtr keys;
	for(groups = doc->children; groups != NULL; groups = groups->next) {
		string groupName = (char*)groups->name;
		for(keys = groups->children; keys != NULL; keys = keys->next) {
			string keyName = (char*)keys->name;
			string keyValue = (char*)keys->content;
			// Convert to a namespace config code
			string configCode = groupName + "_" + keyName;
			transform(configCode.begin(), configCode.end(), configCode.begin(), toupper);
			// Set the relevant ConfigContainer setting
			switch (ConfigReader::configCodes[configCode]) {
				case APPLICATION_URL: config.setAppUrl(keyValue); break;
				case APPLICATION_TITLE: config.setAppTitle(keyValue); break;
				case APPLICATION_WINDOWWIDTH: 
					int width;
					stringstream ssWidth(keyValue);
					ssWidth >> width;
					config.setAppWidth(width); 
					break;
				case APPLICATION_WINDOWHEIGHT: 
					int height;
					stringstream ssHeight(keyValue);
					ssHeight >> height;
					config.setAppHeight(height); 
					break;
			}
		}
	}
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
 * Modify a setting with a new string value
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to change
 * @return the new setting value
 */
void ConfigReader::changeSetting(string group, string key, string newValue) {
	string query = "/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(ConfigReader::getXmlDoc());
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
	if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		result->nodesetval->nodeTab[0]->content = (xmlChar*)newValue.c_str();
	}
	else {
		// TODO: Create new element
		printf("Application setting did not save\n");
	}
	string filePath = ConfigReader::getFilePath();
	//xmlSaveFile((char*)filePath, ConfigReader::getXmlDoc());
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

