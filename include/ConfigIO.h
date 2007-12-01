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

		xmlNodePtr buildAncestors(vector<string> parents); 
		xmlNodePtr findSetting(string group, string key);

	protected:

		ConfigIO(); 
		~ConfigIO();

		xmlDocPtr getXmlDoc() { return xmlDoc; }
		string getFilePath() { return xmlFilePath; }

		void setXmlDoc(xmlDocPtr newDoc) { xmlDoc = newDoc; }
		void setFilePath(string newFilePath) { xmlFilePath = newFilePath; }

		string getSetting(string group, string key, string defaultValue);
		void changeSetting(string group, string key, string newValue);
		void changeSetting(string group, string key, vector<xmlNodePtr> newValue);
	
	public:

		void newFile();

		bool loadFile(string xmlPath);

		bool saveFile();
		bool saveFile(string xmlPath);

};

class ConfigReader : public ConfigIO {

	private:

		string errors;

		void resolveConfigCode(string configCode, ConfigContainer &config, string groupName, xmlNodePtr &key);

		int convertToInt(string strIn);
		bool convertToBoolean(string strIn);
		vector<string> convertToVector(const xmlNodePtr &xmlList, string elementName);
		vector<Rule> convertToGroupedVector(const xmlNodePtr &xmlList);
		Geometry convertToGeometry(const xmlNodePtr &xmlList);
		vector<MenuElement> convertToMenu(const xmlNodePtr &xmlList);

	public:

		ConfigReader(); 
		~ConfigReader() {};

		string getParseErrors() { return this->errors; };

		bool appendConfigToContainer(ConfigContainer &config);

};

class ConfigWriter : public ConfigIO {

	private:

		string convertForXML(int intIn);
		string convertForXML(bool boolIn);
		string convertForXML(const vector<string> &vectorIn, string elementName);
		string convertForXML(const vector<Rule> &vectorIn);
		vector<xmlNodePtr> convertForXML(Geometry geom);

	public:

		ConfigWriter(); 
		~ConfigWriter() {};

		void saveWindowGeometry(ConfigContainer *config);
};

#endif
