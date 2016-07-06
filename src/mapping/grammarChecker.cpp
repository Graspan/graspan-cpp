#include "grammar.h"

Grammar::Grammar(){}

bool Grammar::LoadGrammar(string fname){
	ifstream fin;
	fin.open(fname);
	if(!fin) return false;	

	char str[512]; //for reading original data
	char *p; //token
	vector<string> tok; //for distinguishing rules
	string temp; //temporary storage

	while(!fin.getline(str,sizeof(str)).eof()){
		p = strtok(str,"\t");
		while(p != NULL){
			temp = trimStr(p);
			trimStr(temp);
			tok.push_back(temp);
			//mapping process
			mapping(temp);
			p = strtok(NULL,"\t");
		}

		//e-rule
		if(tok.size() == 1)
			eRules.insert(getValue(tok.at(0)));
		//s-rule
		if(tok.size() == 2)
			sRules[getValue(tok.at(1))]=getValue(tok.at(0));
		//d-rule
		if(tok.size() == 3)
			dRules[changeShort(getValue(tok.at(1)),getValue(tok.at(2)))]=getValue(tok.at(0));
		
		//initialize
		tok.erase(tok.begin(),tok.end());
	}
	fin.close();
	return true;
}

void Grammar::mapping(string temp){
	if(map_info.size() == find(map_info.begin(),map_info.end(),temp) - map_info.begin())
		map_info.push_back(temp);

}

string Grammar::trimStr(string str){
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first,(last - first + 1));
}

inline char Grammar::getValue(string str){
	return (find(map_info.begin(),map_info.end(),str) - map_info.begin());
}

inline short Grammar::changeShort(char a, char b){
	return (short)a << 8 | b;
}

inline vector<string> Grammar::getMapInfo(){
	return map_info;
}

inline set<char> Grammar::getErules(){
	return eRules;
}

char Grammar::check1Rules(string srcVal){
	map<char,char>::iterator it = sRules.find(getValue(srcVal));
	return (it != sRules.end()) ? (*it).second : char(-1);
}

char Grammar::check2Rules(string srcEdgVal, string dstVal){
	short key = changeShort(getValue(srcEdgVal),getValue(dstVal));
	map<short, char>::iterator it = dRules.find(key);
	return (it != dRules.end()) ? (*it).second : char(-1);
}

bool Grammar::print_all(){
	if(!eRules.size() && !sRules.size() && !dRules.size()) return false;
	
	set<char>::iterator it_e; //for eRules
	cout << "eRules" << endl;
	for(it_e=eRules.begin();it_e!=eRules.end();it_e++)
		cout << (short)*it_e << endl;
	
	map<char, char>::iterator it_s; //for sRules
	cout << "sRules" << endl;
	for(it_s=sRules.begin(); it_s!=sRules.end();it_s++)
		cout << (short)(*it_s).first << " -> "  << (short)(*it_s).second << endl;
	
	map<short, char>::iterator it_d; //for dRules
	cout << "dRules" << endl;
	for(it_d=dRules.begin(); it_d!=dRules.end();it_d++)
		cout << ((*it_d).first >> 8) << "," << (short)((char)(*it_d).first) << " -> "  << (short)(*it_d).second << endl;
	return true;
}
