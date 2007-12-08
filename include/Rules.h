#ifndef RULES_DEFINED
#define RULES_DEFINED

#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::endl;
#include "ConfigContainer.h"

class Rules {

	private:

		deque<Rule> ruleList;
		string defaultRule;

	protected:

		bool allowRedirect;
		deque<Rule> getRuleList() { return ruleList; }
		string getDefaultRule() { return defaultRule; }

		virtual bool ruleMatches(Rule rule, string target) { return true; }
		virtual void execRule(Rule rule, string target) {}

	public:

		Rules(deque<Rule> ruleList, string defaultRule);
		Rules() {}
        virtual ~Rules() {}

		bool runRules(string target);
		bool isRedirectAllowed() { return allowRedirect; }
};

class HttpRules : public Rules {

	private:

		bool dropAdverts;

		void handleInternal(string target);
		void handleExternal(string target);
		void handleAdvert(string target);
		void handleDrop(string target);

		bool ruleMatches(Rule rule, string target);
		void execRule(Rule rule, string target);

	public:

		HttpRules(ConfigContainer config);
		virtual ~HttpRules() {}
};

class JavascriptRules : public Rules {

	private:

		bool dropAdverts;

		void handleAllow(string target);
		void handleAdvert(string target);
		void handleDrop(string target);

		bool ruleMatches(Rule rule, string target);
		void execRule(Rule rule, string target);

	public:

		JavascriptRules(ConfigContainer config);
		virtual ~JavascriptRules() {}
};

#endif

