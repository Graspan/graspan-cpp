#include "minset.h"

// constructor
MinSet::MinSet(short numRules)
{
	ptr = 0;

	numEvals = 0;
	evals = new char[numRules];
}



string MinSet::toString()
{
	std::stringstream output;
	
	output << currentVID << ": ";
	for (int n = 0; n < numEvals; n++)
		output << evals[n] << ", ";

	output << endl;

	return output.str();
}

