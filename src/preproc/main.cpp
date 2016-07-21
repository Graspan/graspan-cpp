#include "preproc.h"
#include "../mapping/grammar.cpp"
#include "../loader/loader.h"
#include "repart.h"
#include "../datastructures/context.h"
#include "../DDM/DDM.h"

void delFiles();

int main(int argc, char *argv[]) {

	int numPart = 3;						//it will change numPart = argv[2] or else, userinput
	clock_t begin, end;
	delFiles();
	Grammar g;
	Context c(argc - 2, argv + 2);
	if (!g.loadGrammar("../mapping/grammar")) {			//just for test need to fix
		cout << "file is not exist" << std::endl;
		exit(1);
	}
	Preproc pre(argv[1], c);
	pre.setMapInfo(g.getMapInfo(), g.getErules());
	Loader load;
	begin = clock();
	pre.makeVIT(argv[1], c);		//need to fix input file
	end = clock();
	cout << "makeVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	c.ddm.setNumPartition(pre.getNumOfPartitions());
	c.ddm.enlarge();

	begin = clock();
	pre.makePart(c);
	end = clock();
	cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	c.ddm.save_DDM();
	begin = clock();
	pre.makeBinaryPart(c);
	end = clock();
	cout << "makeBinaryPart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	//cout << c.ddm.toString();
	Partition p1, p2;
	Loader::loadPartition(1,p1, true);
	Loader::loadPartition(2, p2, true);

	cout << p1.toString() << endl;
	c.ddm.load_DDM();

	//Repart::run(p1, p2, c);
	//cout << c.ddm.toString();
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
