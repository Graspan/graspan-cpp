#include "run_pre.h"

int run_preprocessing(Context &context) {
	cout << "##### PREPROCESSING START #####" << endl;

	clock_t begin, end;
	begin = clock();

	Preproc pre(context.getGraphFile(), context);
	pre.setMapInfo(context.grammar.getMapInfo(), context.grammar.getErules());

	//save vit file
	pre.makeVIT(context.getGraphFile(), context);		//need to fix input file
	end = clock();
	//cout << "saveVIT time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	context.ddm.setNumPartition(pre.getNumOfPartitions());
	context.ddm.reSize();

	//save text file
	//begin = clock();
	pre.makePart(context);
	//end = clock();
	//cout << "makePart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	//save binary file and DDM
	context.ddm.save_DDM(context.getGraphFile()+".ddm");
	//begin = clock();
	pre.makeBinaryPart(context);
	end = clock();
	//cout << "makeBinaryPart time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	cout << "PREPROC TIME: " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	return 0;
}
