#ifndef RULES_DEFINED
#define RULES_DEFINED

#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include "ConfigContainer.h"

class Handler {

	private:

		deque<Rule> ruleList;
		string defaultRule;
	
	protected:

		deque<Rule> getRuleList() { return ruleList; }
		string getDefaultRule() { return defaultRule; }

		virtual bool ruleMatches(Rule rule, string target) {}
		virtual void execRule(Rule rule, string target) {}

	public:

		Handler(deque<Rule> ruleList, string defaultRule);

		bool runRules(string target);

};

class DomainHandler : public Handler {

	private:
		
		bool allowRedirect;
		bool dropAdverts;

		void handleInternal(string target);
		void handleExternal(string target);
		void handleAdvert(string target);
		void handleDrop(string target);
	
		bool ruleMatches(Rule rule, string target);
		void execRule(Rule rule, string target);

	public:

		DomainHandler(ConfigContainer config);
		bool isRedirectAllowed() { return allowRedirect; }

};

#endif

