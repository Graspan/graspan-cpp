#include "../../include/grammarchecker.h"


std::unordered_map<std::string, char> GrammarChecker::map = std::unordered_map<std::string, char>{};
std::unordered_map<char, std::string> GrammarChecker::reverse_map = std::unordered_map<char, std::string>{};

std::unordered_map<char, char> GrammarChecker::sRules = std::unordered_map<char, char>{};
std::unordered_map<short, char> GrammarChecker::dRules = std::unordered_map<short, char>{};

short GrammarChecker::make_short(char a, char b)
{
	return (short)((short(a)) << 8 | b);
}

// TODO: Get better trim method
// this seems inefficient
void trimStr(std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	str = str.substr(first, (last - first + 1));
}

// getters
char GrammarChecker::getValue(std::string str)
{
	trimStr(str);
	if (map.find(str) != map.end())
		return map.at(str);
	else
	{
		char c = map.size();
		map.insert({str, c});
		reverse_map.insert({c, str});
		return c;
	}
}

std::string GrammarChecker::getValue(char c)
{
	return reverse_map.at(c);
}


// rule checking
char GrammarChecker::checkL1Rules(char srcVal)
{
	std::unordered_map<char, char>::iterator newVal = sRules.find(srcVal);
	return (newVal != sRules.end()) ? newVal->second : (char(-1));
}

char GrammarChecker::checkL2Rules(char srcEdgVal, char dstVal)
{
	short key = make_short(srcEdgVal, dstVal);
	std::unordered_map<short, char>::iterator newVal = dRules.find(key);
	return (newVal != dRules.end()) ? newVal->second : (char(-1));
}
