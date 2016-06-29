#include "Preproc.h"

void delFiles();

int main(int argc, char *argv[]) {
	int size = 100000;						//test size for each partitions

	delFiles();
	Preproc pre;
	pre.makeVIT("test.txt", size);		//need to fix input is test.txt file
	pre.makePart("test.txt");			//need to fix
	pre.partSort();
	return 0;
}

void delFiles() {//delete test files
	for (int i = 0; i < 20; i++) {
		std::string str = "part" + std::to_string(i);		//need to fix file names
		if (std::ifstream(str))
			std::remove(str.c_str());
		str = "spart" + std::to_string(i);
		if (std::ifstream(str))
			std::remove(str.c_str());
	}
}