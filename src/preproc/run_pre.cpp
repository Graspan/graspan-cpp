#include "run_pre.h"

int run_preprocessing(Context &context) {
	cout << "##### PREPROCESSING START #####" << endl;

	clock_t begin, end;
	begin = clock();

	Preproc pre(argv[1], c);
	pre.setMapInfo(context.grammar.getMapInfo(), context.grammar.getErules());

	//save vit file
	pre.makeVIT(argv[1], c);		//need to fix input file
	end = clock();
	//cout << "saveVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	c.ddm.setNumPartition(pre.getNumOfPartitions());
	c.ddm.enlarge();

	//save text file
	//begin = clock();
	pre.makePart(c);
	//end = clock();
	//cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	//save binary file and DDM
	c.ddm.save_DDM();
	//begin = clock();
	pre.makeBinaryPart(c);
	end = clock();
	//cout << "makeBinaryPart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	cout << "PREPROC TIME: " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	return 0;
}
