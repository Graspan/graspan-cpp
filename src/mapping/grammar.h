#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

class Grammar{
private:
	vector<string> map_info; //for storing map info
	set<char> eRules;
	map<char, char> sRules; 
	map<short, char> dRules;
	void mapping(string temp);
	string trimStr(string str);
	inline char getValue(string str);
	inline short changeShort(char a, char b);
public:
	Grammar();
	bool LoadGrammar(string fname);
	bool print_all();
	inline set<char> getErules();
	char check1Rules(string srcVal);
	char check2Rules(string srcEdgVal, string dstVal);
};
