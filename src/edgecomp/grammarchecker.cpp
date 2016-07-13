#include "grammarchecker.h"


std::unordered_map<string, char> GrammarChecker::map = std::unordered_map<std::string, char>{};
std::unordered_map<char, string> GrammarChecker::reverse_map = std::unordered_map<char, std::string>{};

std::unordered_map<short, char> GrammarChecker::gramRules = std::unordered_map<short, char>{};

short GrammarChecker::make_short(char a, char b)
{
	return (short)((short(a)) << 8 | b);
}

// TODO: Get better trim method
// this seems inefficient
void trimStr(string &str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	str = str.substr(first, (last - first + 1));
}

// getters
char GrammarChecker::getValue(string str)
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

string GrammarChecker::getValue(char c)
{
	return reverse_map.at(c);
}


// rule checking
char GrammarChecker::checkL1Rules(char srcVal)
{
	std::unordered_map<short, char>::iterator newVal = gramRules.find((short)srcVal);
	return (newVal != gramRules.end()) ? newVal->second : (char(-1));
}

char GrammarChecker::checkL2Rules(char srcEdgVal, char dstVal)
{
	std::unordered_map<short, char>::iterator newVal = gramRules.find(make_short(srcEdgVal, dstVal));
	return (newVal != gramRules.end()) ? newVal->second : (char(-1));
}



// test ---- delete later
void GrammarChecker::addSRule(char src, char dst)
{
	gramRules.insert({(short)src, dst});
}

void GrammarChecker::addDRule(char src, char dst, char newedge)
{
	gramRules.insert({make_short(src, dst), newedge});
}
