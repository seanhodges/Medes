#ifndef STRINGENUM_DEFINED
#define STRINGENUM_DEFINED

#include <string>
	using std::string;
#include <map>
	using std::map;

class StringEnum {

	private:
		
		int enumIndex;

		map<string, int> enumArray;

	public:

		StringEnum();

		~StringEnum();

		void declare(string identifier);

		int resolve(string identifier);

};

#endif
