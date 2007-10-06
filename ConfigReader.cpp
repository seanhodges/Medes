#include "ConfigReader.h"
#include <libxml/tree.h>
#include <libxml/xpath.h>

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
void ConfigReader::appendConfigToContainer(ConfigContainer* config) {
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
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

