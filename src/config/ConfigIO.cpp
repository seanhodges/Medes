#include <libxml/tree.h>
#include <libxml/xpath.h> 
#include <iostream>
	using std::cout;
	using std::endl;
#include <fstream>
	using std::ifstream;
	using std::ofstream;
#include "ConfigIO.h"

/**
 * Initialise libxml
 */
ConfigIO::ConfigIO() {
	xmlInitParser();
	LIBXML_TEST_VERSION
}

/**
 * Shut down libxml
 */
ConfigIO::~ConfigIO() {
	// Causes a segmentation fault, think it's needed?
	//xmlFreeDoc(ConfigReader::getXmlDoc());
	xmlCleanupParser();
}

/**
 * Load a config XML
 *
 * @param xmlPath - the file path to the config XML
 */
bool ConfigIO::loadFile(string xmlPath) {
	ifstream fin(xmlPath.c_str());
	if(fin) {
		this->xmlFilePath = xmlPath;
		this->xmlDoc = xmlParseFile(xmlPath.c_str());
		fin.close();
		return true;
	}
	return false;
}

/**
 * Save a config XML
 *
 * @param xmlPath - (optional) save to this path
 */
bool ConfigIO::saveFile(string xmlPath = "") {
	// Default to overwriting last loaded file
	if (xmlPath == "") xmlPath = this->xmlFilePath;
	ofstream fout(xmlPath.c_str());
	if(fout) {
		xmlSaveFile(xmlPath.c_str(), this->xmlDoc);
		fout.close();
		return true;
	}
	return false;
}

/**
 * Return a setting
 *
 * @param group - the "group" node that the setting is contained in
 * @param key - the setting to return
 * @return the string representation of the setting value
 */
string ConfigIO::getSetting(string group, string key, string defaultValue) {
	string resultVal; 
	string query = "/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(this->xmlDoc);
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
void ConfigIO::changeSetting(string group, string key, string newValue) {
	// TODO: Finish and test this method
	string query = "/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(this->xmlDoc);
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
	if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		result->nodesetval->nodeTab[0]->content = (xmlChar*)newValue.c_str();
	}
	else {
		// TODO: Create new element
	}
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

