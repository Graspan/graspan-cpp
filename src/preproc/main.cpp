#include "Preproc.h"
#include "../mapping/grammarChecker.cpp"

void delFiles();

int main(int argc, char *argv[]) {
	int numPart = 10;						//it will change numPart = argv[2] or else, userinput
	clock_t begin, end;

	delFiles();
	Grammar g;
	if (!g.LoadGrammar("../mapping/grammar")) {			//just for test need to fix
		std::cout << "file is not exist" << std::endl;
		exit(1);
	}
	Preproc pre("test.txt", numPart);
	pre.setMapInfo(g.getMapInfo(), g.getErules());

	begin = clock();
	pre.makeVIT("test.txt");		//need to fix input file
	end = clock();
	std::cout << "makeVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makePart(0);			//if 0 then get mapped label else if 1 get label
	end = clock();
	std::cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	return 0;
}

void delFiles() {//delete test files
	for (int i = 0; i < 200; i++) {
		std::string str = "part" + std::to_string(i);		//need to fix file names
		if (std::ifstream(str))
			std::remove(str.c_str());
		str = "spart" + std::to_string(i);
		if (std::ifstream(str))
			std::remove(str.c_str());
	}
}