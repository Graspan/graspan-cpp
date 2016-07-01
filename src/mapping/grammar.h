#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class Grammar{
	char str[512];
	char *p; //token
	vector<string> tok;
	vector<string> mapp;
	set<char> eRules;
	map<char, char> sRules; 
	map<short, char> dRules;
public:
	Grammar();
	char getValue(string str);
	void GrammarCheck();
	string trimStr(string str);
	short changeShort(char a, char b);
	void print_e();
	void print_s();
	void print_d();
};
