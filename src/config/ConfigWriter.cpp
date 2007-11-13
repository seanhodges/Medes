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
	// Currently, always saves to userWebAppPath,
	// this avoids permissions problems, and keeps things simple for now
	Environment env;
	string target = env.getUserWebAppPath() + "googlemaps.xml";
	bool success = loadFile(target);
	if (!success) {
		newFile();
	}
}

/**
 * Save the current window geometry to the XML
 *
 * @param config - the ConfigContainer object to read
 */
void ConfigWriter::saveWindowGeometry(ConfigContainer *config) {
	changeSetting("application", "windowgeometry", convertForXML(config->getWindowGeom()));
	saveFile();
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
 * Cast a vector to an XML-friendly string
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
 * Cast a rule vector to an XML-friendly string
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
 * Cast a geometry to an XML-friendly string
 *
 * @param geomIn - the geometry to convert into XML
 *
 * @return the XML as a string
 */
string ConfigWriter::convertForXML(Geometry vectorIn) {
	//TODO: Complete this implementation
	return "<left>0</left><top>0</top><width>500</width><height>300</height>";
}

