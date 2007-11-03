#ifndef CONFIGIO_DEFINED
#define CONFIGIO_DEFINED

#include <libxml/xmlreader.h>
#include <string>
	using std::string;
#include <vector>
	using std::vector;
#include "ConfigContainer.h"

class ConfigIO {

	private:

		string xmlFilePath;

		xmlDocPtr xmlDoc;

	protected:

		ConfigIO(); 
		~ConfigIO();

		xmlDocPtr getXmlDoc() { return xmlDoc; }
		string getFilePath() { return xmlFilePath; }

		void setXmlDoc(xmlDocPtr newDoc) { xmlDoc = newDoc; }
		void setFilePath(string newFilePath) { xmlFilePath = newFilePath; }

		bool loadFile(string xmlPath);
		bool saveFile(string xmlPath);

		string getSetting(string group, string key, string defaultValue);
		void changeSetting(string group, string key, string newValue);

};

class ConfigReader : public ConfigIO {

	private:

		void resolveConfigCode(string configCode, ConfigContainer &config, string groupName, xmlNodePtr &key);

		int convertToInt(string &strIn);
		bool convertToBoolean(string &strIn);
		vector<string> convertToVector(const xmlNodePtr &xmlList, string elementName);
		vector<GroupedEntry> convertToGroupedVector(const xmlNodePtr &xmlList);

	public:

		ConfigReader(); 
		~ConfigReader() {};

		bool loadConfig(string xmlPath);

		void appendConfigToContainer(ConfigContainer &config);

};

class ConfigWriter : public ConfigIO {

	private:

		string convertForXML(int intIn);
		string convertForXML(bool boolIn);
		string convertForXML(const vector<string> &vectorIn, string elementName);
		string convertForXML(const vector<GroupedEntry> &vectorIn);

	public:

		ConfigWriter(); 
		~ConfigWriter() {};

		void saveWindowGeometry(ConfigContainer &config);
};

#endif
