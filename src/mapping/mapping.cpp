#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	ifstream fin;
	fin.open("grammar");

	char g;
	vector<char> cmp;
	while(!fin.eof()){
		fin	>> g;
		if(cmp.size() == find(cmp.begin(),cmp.end(),g) - cmp.begin()) 
			cmp.push_back(g);
	}

	int pos;
	for(int i=0; i<cmp.size(); i++){
		pos = find(cmp.begin(),cmp.end(),cmp.at(i)) - cmp.begin();
		cout << cmp.at(i) << " -> " << pos << endl;
	}

	fin.close();
}
