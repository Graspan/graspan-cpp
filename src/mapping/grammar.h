#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "../utilities/globalDefinitions.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <cstring>
#include <vector>
#include <map>

using std::vector;
using std::set;
using std::map;

class Grammar{
  
 private:

  vector<raw_label_t> map_info; //for storing map info

  set<label_t> eRules; //encoded form
  
  map<short, label_t> rules;
	
  void mapping(raw_label_t temp);
  
  string trimStr(string str);
	
  inline label_t getValue(raw_label_t str);
	
  inline short changeShort(label_t a, label_t b);
 
 public:
	
  Grammar();
  ~Grammar();

  bool loadGrammar(string fname);
	
  bool print_all();

  //if using map_info with rules, have to subtract 1	
  inline vector<raw_label_t> getMapInfo() {
    return map_info;
  }
	
  inline set<label_t> getErules() {
    return eRules;
  }

	label_t checkRules(string srcVal, string dstVal);

  label_t checkRules(label_t srcVal, label_t dstVal);

};


#endif
