#ifndef CONFIGREADER_DEFINED
#define CONFIGREADER_DEFINED

#include <libxml/xmlreader.h>
#include <string>
	using namespace std;

class ConfigReader {

	private:

		template<typename T> T getSetting(string group, string key);

		struct ConfigResult {

			ConfigResult(ConfigReader& reader, string group, string key)
				: reader(reader), group(group), key(key) {}

			template<typename T> operator T() {
				return reader.getSetting<T>(group, key);
			}

			ConfigReader& reader;
				
			string group;

			string key;
			
		};

		string xmlDoc;

	public:

		ConfigReader(string xmlPath); 

		ConfigResult getSetting(string group, string key);

		void changeSetting(string group, string key, string newValue);
};

#endif
