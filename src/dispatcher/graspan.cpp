#include "../../test/timer.h"
#include "../edgecomp/engine.h"
#include "../datastructures/vit.h"

#include "../utilities/globalDefinitions.hpp"

int main(int argc, char *argv[])
{
	Context c(argc, argv);

	if (!c.ddm.load_DDM("DDM")) {
		cout << "execution failed: couldn't load DDM" << endl;
		return 12;
	}

	if (!c.grammar.loadGrammar("grammar")) {
		cout << "execution failed: couldn't load grammar" << endl;
		return 12;
	}

	VIT::loadFromFile(c.vit);


	// COMPUTATION
	Timer compTime;
	compTime.startTimer();

	run_computation(c);

	compTime.endTimer();
	cout << compTime.toString() << endl;

	return 0;
}
