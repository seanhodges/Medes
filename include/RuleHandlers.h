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

		deque<GroupedEntry> ruleList;
		string defaultRule;
	
	protected:

		deque<GroupedEntry> getRuleList() { return ruleList; }
		string getDefaultRule() { return defaultRule; }

	public:

		Handler(deque<GroupedEntry> ruleList, string defaultRule);

		bool runRules(string target);

		virtual bool ruleMatches(GroupedEntry rule, string target) {}
		virtual void execRule(GroupedEntry rule, string target) {}

};

class DomainHandler : public Handler {

	private:
		
		bool allowRedirect;
		bool dropAdverts;

		void handleInternal(string target);
		void handleExternal(string target);
		void handleAdvert(string target);
		void handleDrop(string target);
	
	public:

		DomainHandler(ConfigContainer config);

		bool ruleMatches(GroupedEntry rule, string target);
		void execRule(GroupedEntry rule, string target);

};

#endif

