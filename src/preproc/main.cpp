#include "Preproc.h"

void delFiles();

int main(int argc, char *argv[]) {
	int numPart = 10;						//it will change numPart = argv[2] or else, userinput
	clock_t begin, end;

	delFiles();
	Preproc pre("test.txt", numPart);

	begin = clock();
	pre.makeVIT("test.txt");		//need to fix input file
	end = clock();
	std::cout << "makeVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	begin = clock();
	pre.makePart();
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