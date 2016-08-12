#include "minset.h"

// constructor
MinSet::MinSet(short numRules)
{
	ptr = 0;
	evals = new char[numRules];
}

MinSet::~MinSet()
{
	delete evals[];
}


string MinSet::toString()
{
	std::stringstream output;
	
	output << currentVID << ": ";
	for (int i = 0; i < numEvals; i++)
		output << (short)evals[i] << ", ";

	output << endl;

	return output.str();
}

