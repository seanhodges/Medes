#ifndef CONFIGREADER_DEFINED
#define CONFIGREADER_DEFINED

#include <libxml/xmlreader.h>
#include <string>
	using std::string;
#include "ConfigContainer.h"

class ConfigReader {

	private:

		string xmlFilePath;

		xmlDocPtr xmlDoc;

		int convertToInt(string& strIn);

	public:

		ConfigReader(); 
		~ConfigReader();

		xmlDocPtr getXmlDoc() { return xmlDoc; }
		string getFilePath() { return xmlFilePath; }

		void setXmlDoc(xmlDocPtr newDoc) { xmlDoc = newDoc; }
		void setFilePath(string newFilePath) { xmlFilePath = newFilePath; }

		bool loadFile(string xmlPath);

		void appendConfigToContainer(ConfigContainer& config);

		string getSetting(string group, string key, string defaultValue);

		void changeSetting(string group, string key, string newValue);
};

#endif
