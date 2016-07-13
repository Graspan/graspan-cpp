#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <cstring>
#include <vector>
#include <map>

//using namespace std;

using std::vector;
using std::string;
using std::set;
using std::map;

class Grammar{
  
 private:

  vector<string> map_info; //for storing map info

  set<char> eRules; //encoded form
  
  std::map<short, char> rules;
	
  void mapping(string temp);
  
  string trimStr(string str);
	
  inline char getValue(string str);
	
  inline short changeShort(char a, char b);
 
 public:
	
  Grammar();
  ~Grammar();

  bool loadGrammar(string fname);
	
  bool print_all();

  //if using map_info with rules, have to subtract 1	
  inline vector<string> getMapInfo() {
    return map_info;
  }
	
  inline set<char> getErules() {
    return eRules;
  }

	char checkRules(string srcVal, string dstVal);

  char checkRules(char srcVal, char dstVal);

};
