#include "preproc.h"
#include "../mapping/grammarChecker.cpp"
#include "../loader/loader.h"

void delFiles();

int main(int argc, char *argv[]) {
	int numPart = 3;						//it will change numPart = argv[2] or else, userinput
	clock_t begin, end;
	delFiles();
	Grammar g;
	if (!g.loadGrammar("../mapping/grammar")) {			//just for test need to fix
		cout << "file is not exist" << std::endl;
		exit(1);
	}
	Preproc pre("test.txt", numPart);
	pre.setMapInfo(g.getMapInfo(), g.getErules());
	Loader load;
	begin = clock();
	pre.makeVIT("test.txt");		//need to fix input file
	end = clock();
	cout << "makeVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makePart();
	end = clock();
	cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makeBinaryPart();
	end = clock();
	cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	Partition p;
	Loader::loadPartition(1,p, false);
	Partition::writeToFile(p, true);
	return 0;
}

void delFiles() {//delete test files
	string str;
	for (int i = 0; i < 200; i++) {
		str = GRAP + "." + PART + "." + HUMA + "." + std::to_string((long long)i);		//need to fix file names
		if (std::ifstream(str))
			std::remove(str.c_str());
		str = GRAP + "." + PART + "." + BINA + "." + std::to_string((long long)i);
		if (std::ifstream(str))
			std::remove(str.c_str());
	}
}
