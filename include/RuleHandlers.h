#ifndef RULES_DEFINED
#define RULES_DEFINED

#include <string>
	using std::string;
#include "ConfigContainer.h"

class Handler {

	private:

		deque<GroupedEntry> ruleList;
		string defaultRule;
	
	protected:

		deque<GroupedEntry> getRuleList() { return ruleList; }
		string getDefaultRule() { return defaultRule; }

	public:

		Handler(deque<GroupedEntry> ruleList, string defaultRule);

		bool runRules(string target);

		virtual bool hasRule(string ruleName) {}
		virtual void execRule(string ruleName, string target) {}

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

