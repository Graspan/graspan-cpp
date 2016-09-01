#include "../../test/timer.h"
#include "../edgecomp/engine.h"
#include "../preproc/run_pre.h"
#include "../datastructures/vit.h"

#include "../utilities/globalDefinitions.hpp"

int main(int argc, char *argv[])
{
	Timer graspanTimer, prepTimer, compTimer;
	graspanTimer.startTimer();
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
	prepTimer.startTimer();

	cout << "###### STARTING PREPROCESSING #####" << endl;
	if (c.ddm.getNumPartition() != c.vit.getNumPartition() || c.vit.getNumPartition() == 0) {
		run_preprocessing(c);
	}

	prepTimer.endTimer();
	return 0;
	// COMPUTATION
	compTimer.startTimer();

	cout << "###### STARTING COMPUTATION #####" << endl;
	run_computation(c);

	compTimer.endTimer();

	graspanTimer.endTimer();
	std::cerr << "===== GRASPAN FINISHED =====" << endl;
	cout << "TOTAL PREPROC TIME: " << prepTimer.hmsFormat() << endl;
	cout << "TOTAL COMPUTE TIME: " << compTimer.hmsFormat() << endl;
	cout << "TOTAL GRASPAN TIME: " << graspanTimer.hmsFormat() << "\n" << endl;

	return 0;
}
