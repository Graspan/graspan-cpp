#include "../edgecomp/engine.h"

int main(int argc, char *argv[])
{
	Context c(argc, argv);

	if (!c.ddm.load_DDM()) {
		cout << "execution failed: couldn't load DDM" << endl;
		return 12;
	}

	if (!c.grammar.loadGrammar("grammar")) {
		cout << "execution failed: couldn't load grammar" << endl;
		return 12;
	}

	run_computation(c);

	return 0;
}
