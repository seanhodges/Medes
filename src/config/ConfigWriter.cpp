#include <sstream>
	using std::stringstream;
#include <iostream>
	using std::cout;
	using std::endl;
#include "ConfigIO.h"
#include "Environment.h"

/**
 * Create a new ConfigWriter object
 */
ConfigWriter::ConfigWriter() 
	: ConfigIO::ConfigIO() { 
	newFile();
}

/**
 * Save the current window geometry to the XML
 *
 * @param config - the ConfigContainer object to read
 */
void ConfigWriter::saveWindowGeometry(ConfigContainer *config) {
	changeSetting("application", "windowgeometry", convertForXML(config->getWindowGeom()));
	bool success = saveFile();
	if (!success) {
		cout << "warning: cannot save the window geometry to the local user config" << endl;
	}
}

/**
 * Cast an int setting to an XML-friendly string
 *
 * @param intIn - the int to parse
 *
 * @return the string value
 */
string ConfigWriter::convertForXML(int intIn) {
	string strOut = "0";
	stringstream ss(strOut);
	ss << intIn;
	if (ss.fail()) {
		cout << intIn + " is not a number" << endl;
	}
	else {
		ss >> strOut;
	}
	return strOut;
}

/**
 * Cast an boolean setting to an XML-friendly string
 *
 * @param boolIn - the boolean to parse
 *
 * @return the string value
 */
string ConfigWriter::convertForXML(bool boolIn) {
	string strOut = "false";
	if (boolIn) strOut = "true";
	return strOut;
}

/**
 * Cast a vector to an XML structure
 *
 * @param vectorIn - the vector to convert into XML
 * @param elementName - all child nodes will have this name
 *
 * @return the XML as a string
 */
string ConfigWriter::convertForXML(const vector<string> &vectorIn, string elementName) {
	//TODO: Complete this implementation
	return "";
}

/**
 * Cast a rule vector to an XML structure
 *
 * @param vectorIn - the vector to convert into XML
 *
 * @return the XML as a string
 */
string ConfigWriter::convertForXML(const vector<Rule> &vectorIn) {
	//TODO: Complete this implementation
	return "";
}

/**
 * Cast a geometry to an XML structure
 *
 * @param geomIn - the geometry to convert into XML
 *
 * @return the XML as a node
 */
vector<xmlNodePtr> ConfigWriter::convertForXML(Geometry geomIn) {
	//TODO: Complete this implementation
	vector<xmlNodePtr> out;
	xmlNodePtr leftNode = xmlNewNode(NULL, BAD_CAST "left");
	xmlNodeSetContent(leftNode, (xmlChar*)convertForXML(geomIn.getLeft()).c_str());
	out.push_back(leftNode);
	xmlNodePtr topNode = xmlNewNode(NULL, BAD_CAST "top");
	xmlNodeSetContent(topNode, (xmlChar*)convertForXML(geomIn.getTop()).c_str());
	out.push_back(topNode);
	xmlNodePtr widthNode = xmlNewNode(NULL, BAD_CAST "width");
	xmlNodeSetContent(widthNode, (xmlChar*)convertForXML(geomIn.getWidth()).c_str());
	out.push_back(widthNode);
	xmlNodePtr heightNode = xmlNewNode(NULL, BAD_CAST "height");
	xmlNodeSetContent(heightNode, (xmlChar*)convertForXML(geomIn.getHeight()).c_str());
	out.push_back(heightNode);
	return out;
}

