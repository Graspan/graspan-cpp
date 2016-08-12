#ifndef MINSET_H
#define MINSET_H

#include <unordered_set>
#include <string>
#include <sstream>

#include "../utilities/globalDefinitions.hpp"

class MinSet
{
	int ptr;
	
	int minSetID;
	int currentVID;
	char *evals;
	int numEvals;

	public:
	// constructor
	MinSet(short numRules);
	~MinSet();

	// getters
	inline int getMinSetID() { return minSetID; }
	inline int getCurrVID() const { return currentVID; }
	inline int getPtr() { return ptr; }
	inline int getNumEvals() { return numEvals; }
	inline char *getEvals() { return evals; }

	// setters
	inline void setMinSetID(int id) { minSetID = id; }
	inline void setCurrVID(int vid) { currentVID = vid; }
//	inline void resetPtr() { ptr = 0; numEvals = 0; }

	inline void incPtr() { ptr++; }
	inline void addEval(char eval) { evals[numEvals] = eval; }
	inline void clearEvalSet() { numEvals = 0; }
	
	string toString();
};

// sort minsets in a priority queue
class compare
{
	public:
	bool operator()(const MinSet &m1, const MinSet &m2) const
	{
		return m1.getCurrVID() > m2.getCurrVID();
	}
};

#endif
