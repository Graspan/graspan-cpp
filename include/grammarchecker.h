#ifndef GRAMMARCHECKER_H
#define GRAMMARCHECKER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class GrammarChecker
{
	
	public:
	static std::unordered_map<std::string, char> map;
	static std::unordered_map<char, std::string> reverse_map;
	static std::unordered_map<short, char> gramRules;

	static short make_short(char a, char b);

	// MOVE PUBLIC BACK TO HERE AFTER DONE TESTING
	static std::unordered_set<char> eRules;

	// getters
	static char getValue(std::string str);
	static std::string getValue(char c);

	// rule checking
	static char checkL1Rules(char srcVal);
	static char checkL2Rules(char srcEdgVal, char dstVal);

	static void addSRule(char src, char dst);
	static void addDRule(char src, char dst, char newedge);
};

#endif
