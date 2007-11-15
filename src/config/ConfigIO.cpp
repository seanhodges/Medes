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
	newFile();
}

/**
 * Shut down libxml
 */
ConfigIO::~ConfigIO() {
	xmlFreeDoc(this->xmlDoc);
	xmlCleanupParser();
}

void ConfigIO::newFile() {
	this->xmlDoc = xmlNewDoc(BAD_CAST "1.0");
}

/**
 * Load a config XML
 *
 * @param xmlPath - the file path to the config XML
 */
bool ConfigIO::loadFile(string xmlPath) {
	ifstream fin;
	fin.open(xmlPath.c_str());
	if(fin) {
		this->xmlFilePath = xmlPath;
		this->xmlDoc = xmlParseFile(xmlPath.c_str());
		fin.close();
		return true;
	}
	return false;
}

/**
 * Overwrite the config XML
 *
 * @return true if the save was successful
 */
bool ConfigIO::saveFile() {
	return saveFile(this->xmlFilePath);
}

/**
 * Save the config XML to a defined location
 *
 * @param xmlPath - the target file path to save to
 *
 * @return true if the save was successful
 */
bool ConfigIO::saveFile(string xmlPath) {
	cout << "Saving to " + xmlPath << endl;
	int fileSize = xmlSaveFormatFile(xmlPath.c_str(), this->xmlDoc, 1);
	return (fileSize > -1);
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
	string query = "/webapp/" + group + "/" + key;
	xmlChar* xpath = (xmlChar*)query.c_str();
	xmlXPathContextPtr context = xmlXPathNewContext(this->xmlDoc);
	xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
	xmlNodeSetPtr resultNodes = result->nodesetval;
	if (!xmlXPathNodeSetIsEmpty(resultNodes)) {
		cout << "changing " << query << " to " << newValue << endl;
		xmlNodeSetContent(resultNodes->nodeTab[0], (xmlChar*)newValue.c_str());
	}
	else {
		// TODO: Create new element
		cout << "NOT SUPPOSED TO BE HERE!" << endl;
	}
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

