#include "grammar.h"

int main(){

  using std::cout; using std::cin; using std::endl;

	string fname;

	cout << "insert the file name : ";
	cin >> fname;
	Grammar g;
	if(!g.loadGrammar(fname)){
		cout << "file is not exist" << endl;
		exit(1);
	}
	if(!g.print_all()){
		cout << "data is empty" << endl;
		exit(2);
	}

	g.getErules();
}
