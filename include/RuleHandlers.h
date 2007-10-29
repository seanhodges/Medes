#ifndef RULES_DEFINED
#define RULES_DEFINED

#include <string>
	using std::string;
#include "ConfigContainer.h"

class Handler {

	private:

		ConfigContainer config;
	
	protected:

		ConfigContainer getConfig() { return config; }

	public:

		Handler(ConfigContainer config);

		bool runRules(string target);

		virtual bool hasRule(string ruleName) {};
		virtual void execRule(string ruleName, string target) {};

};

class DomainHandler : public Handler {

	private:
		
		bool allowRedirect;
	
	public:

		DomainHandler(ConfigContainer config);

		bool isRedirectAllowed() { return allowRedirect; }

		bool hasRule(string ruleName);
		void execRule(string ruleName, string target);

};

#endif

