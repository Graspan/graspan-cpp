#include "../../test/timer.h"
#include "../edgecomp/engine.h"
#include "../preproc/run_pre.h"
#include "../datastructures/vit.h"

#include "../utilities/globalDefinitions.hpp"

int main(int argc, char *argv[])
{
	Context c(argc, argv);

	if (!c.ddm.load_DDM(c.getGraphFile() + ".ddm")) {
		cout << "execution failed: couldn't load DDM" << endl;
		//return 12;
	}

	if (!c.grammar.loadGrammar(c.getGrammarFile())) {
		cout << "execution failed: couldn't load grammar" << endl;
		return 12;
	}
	
	if (!c.vit.loadFromFile(c.getGraphFile() + ".vit")) {
		cout << "execution failed: couldn't load VIT" << endl;
		//return 12;
	}
	
	// PREPROCESSING
	Timer compTime;
	compTime.startTimer();

	cout << "###### STARTING PREPROCESSING #####" << endl;
	if (c.ddm.getNumPartition() != c.vit.getNumVertex() || c.vit.getNumVertex() == 0) {
		run_preprocessing(c);
	}

	compTime.endTimer();
	cout << "TOTAL TIME: " << compTime.toString() << endl;



	// COMPUTATION
	compTime.startTimer();

	cout << "###### STARTING COMPUTATION #####" << endl;
	run_computation(c);

	compTime.endTimer();
	cout << "TOTAL TIME: " << compTime.toString() << endl;

	std::cerr << "GRASPAN FINISHED" << endl;

	return 0;
}
