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
	std::unordered_set<char> evals;


	public:
	// constructor
	MinSet();

	// getters
	int getMinSetID();
	int getCurrVID() const;
	int getPtr();
	std::unordered_set<char> &getEvals();

	// setters
	void setMinSetID(int id);
	void setCurrVID(int vid);
	void resetPtr();

	void incPtr();
	void addEval(char eval);
	void clearEvalSet();
	
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
