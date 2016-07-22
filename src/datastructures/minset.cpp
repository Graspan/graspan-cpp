#include "minset.h"

// constructor
MinSet::MinSet()
{
	ptr = 0;
}

// getters
int MinSet::getMinSetID() { return minSetID; }
int MinSet::getCurrVID() const { return currentVID; }
int MinSet::getPtr() { return ptr; }
std::unordered_set<char>& MinSet::getEvals() { return evals; }

// setters
void MinSet::setMinSetID(int id) { minSetID = id; }
void MinSet::setCurrVID(int vid) { currentVID = vid; }
void MinSet::resetPtr() { ptr = 0; }

void MinSet::incPtr() { ptr++; }

void MinSet::addEval(char eval) { evals.insert(eval); }

void MinSet::clearEvalSet() { evals.clear(); }

string MinSet::toString()
{
	std::stringstream output;
	
	output << currentVID << ": ";
	for (std::unordered_set<char>::iterator it = evals.begin(); it != evals.end(); it++)
		output << (short)*it << ", ";

	output << endl;

	return output.str();
}

