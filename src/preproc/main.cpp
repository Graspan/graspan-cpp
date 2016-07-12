#include "Preproc.h"
#include "../mapping/grammarChecker.cpp"
#include "../loader/Loader.h"

void delFiles();

int main(int argc, char *argv[]) {
	int numPart = 3;						//it will change numPart = argv[2] or else, userinput
	clock_t begin, end;

	delFiles();
	Grammar g;
	if (!g.LoadGrammar("../mapping/grammar")) {			//just for test need to fix
		std::cout << "file is not exist" << std::endl;
		exit(1);
	}
	Preproc pre("test.txt", numPart);
	pre.setMapInfo(g.getMapInfo(), g.getErules());
	Loader load;

	begin = clock();
	pre.makeVIT("test.txt");		//need to fix input file
	end = clock();
	std::cout << "makeVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makePart();			//if 0 then get mapped label else if 1 get label
	end = clock();
	std::cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makeBinaryPart();			//if 0 then get mapped label else if 1 get label binaryfile
	end = clock();
	std::cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;


	load.loadBinary("bpart0");
	return 0;
}

void delFiles() {//delete test files
	for (int i = 0; i < 200; i++) {
		std::string str = "part" + std::to_string((long long)i);		//need to fix file names
		if (std::ifstream(str))
			std::remove(str.c_str());
		str = "spart" + std::to_string((long long)i);
		if (std::ifstream(str))
			std::remove(str.c_str());
		str = "bpart" + std::to_string((long long)i);
		if (std::ifstream(str))
			std::remove(str.c_str());
	}
}
