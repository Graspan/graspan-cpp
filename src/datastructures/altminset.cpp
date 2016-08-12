#include "minset.h"

// constructor
MinSet::MinSet(/*short numRules*/)
{
	ptr = 0;
}



string MinSet::toString()
{
	std::stringstream output;
	
	output << currentVID << ": ";
	for (std::unordered_set<char>::iterator it = evals.begin(); it != evals.end(); it++)
		output << (short)*it << ", ";

	output << endl;

	return output.str();
}

