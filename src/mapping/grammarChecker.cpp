#include "grammar.h"

Grammar::Grammar(){}

void Grammar::GrammarCheck(){
	ifstream fin;
	fin.open("grammar");

	string temp;
	while(!fin.getline(str,sizeof(str)).eof()){
		p = strtok(str,"\t");
		while(p != NULL){
			temp = trimStr(p);
			trimStr(temp);
			tok.push_back(temp);
			if(mapp.size() == find(mapp.begin(),mapp.end(),temp) - mapp.begin())
				mapp.push_back(temp);
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
}

string Grammar::trimStr(string str){
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first,(last - first + 1));
}

char Grammar::getValue(string str){
	return (find(mapp.begin(),mapp.end(),str) - mapp.begin());
}

short Grammar::changeShort(char a, char b){
	return (short)a << 8 | b;
}

void Grammar::print_e(){
	set<char>::iterator it;
	cout << "eRules" << endl;
	for(it=eRules.begin();it!=eRules.end();it++)
		cout << (short)*it << endl;
}

void Grammar::print_s(){
	map<char, char>::iterator it;
	cout << "sRules" << endl;
	for(it=sRules.begin(); it!=sRules.end();it++)
		cout << (short)(*it).first << " -> "  << (short)(*it).second << endl;
}

void Grammar::print_d(){
	map<short, char>::iterator it;
	cout << "dRules" << endl;
	for(it=dRules.begin(); it!=dRules.end();it++)
		cout << ((*it).first >> 8) << "," << (short)((char)(*it).first) << " -> "  << (short)(*it).second << endl;
}

int main(){
	Grammar g;
	g.GrammarCheck();
	g.print_e();
	g.print_s();
	g.print_d();
}
