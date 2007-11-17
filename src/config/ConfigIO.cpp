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

/**
 * Create a new config file
 */
void ConfigIO::newFile() {
	this->xmlDoc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root_element = xmlNewNode(NULL, BAD_CAST "webapp");
	xmlDocSetRootElement(this->xmlDoc, root_element);
}

/**
 * Load a config XML
 *
 * @param xmlPath - the file path to the config XML
 */
bool ConfigIO::loadFile(string xmlPath) {
	ifstream fin;
	this->xmlFilePath = xmlPath;
	fin.open(xmlPath.c_str());
	if(fin) {
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
		// Create new child element
		cout << "setting " << query << " to " << newValue << endl;
		vector<string> parents;
		parents.push_back(group);
		parents.push_back(key);
		xmlNodePtr newNode = buildAncestors(parents);
		xmlNodeAddContent(newNode, (xmlChar*)newValue.c_str());
	}
	xmlXPathFreeContext(context);
	xmlXPathFreeObject(result);
}

/**
 * Build the path up to a target node
 *
 * @param parents - array of parent nodes to check/create
 *
 * @return the target node 
 */
xmlNodePtr ConfigIO::buildAncestors(vector<string> parents) {
	cout << "building path to node" << endl;
	xmlXPathContextPtr context = xmlXPathNewContext(this->xmlDoc);
	string query = "/webapp";
	xmlNodePtr parentNode = xmlDocGetRootElement(this->xmlDoc);
	xmlNodePtr newNode; 
	// Traverse the required ancestors, and create them as required
	for (vector<string>::iterator it = parents.begin(); it != parents.end(); it++) {
		query = query + "/" + *it;
		xmlChar* xpath = (xmlChar*)query.c_str();
		xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
		xmlNodeSetPtr resultNodes = result->nodesetval;
		if (xmlXPathNodeSetIsEmpty(resultNodes)) {
			// This ancestor does not exist, create it
			cout << "creating ancestor \"" << *it << "\"" << endl;
			newNode = xmlNewChild(parentNode, NULL, BAD_CAST (xmlChar*)it->c_str(), NULL);
		}
		// Move up the query
		parentNode = xmlNodePtr(newNode);
	}
	return parentNode;
}
