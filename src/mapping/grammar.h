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
	map<short, char> rules;
	void mapping(string temp);
	string trimStr(string str);
	inline char getValue(string str);
	inline short changeShort(char a, char b);
public:
	Grammar();
	bool LoadGrammar(string fname);
	bool print_all();
	inline vector<string> getMapInfo();
	inline set<char> getErules();
};
