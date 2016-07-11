#ifndef EDGEMERGER_H
#define EDGEMERGER_H

#include <iostream>
#include <ctime>
#include <limits>
#include <unordered_set>
#include <queue>

#include "../datastructures/minset.h"
#include "../../test/timer.h"

class EdgeMerger
{
	int deltaPtr;
	int oUnUdPtr;
	int currID;

	std::unordered_set<char> currEvals;
	std::priority_queue<MinSet, std::vector<MinSet>, compare> minEdges;

	std::vector<int> srcoUnUdEdges;
	std::vector<char> srcoUnUdVals;

	std::vector<int> srcDeltaEdges;
	std::vector<char> srcDeltaVals;


	// FUNCTIONS
	void removeExtraSpace();

	void updateMinSet(MinSet &minset, std::vector<int> &edges, std::vector<char> &vals);

	void processMinSets(MinSet &srcMS, MinSet &tgtMS, std::vector<int> &srcEdgesToMerge,
		std::vector<char> &srcValsToMerge, std::vector<int> &tgtEdgesToMerge,
		std::vector<char> &tgtValsToMerge);

	public:
	// constructor
	EdgeMerger();

	// getters
	std::vector<int> getoUnUdEdges();
	std::vector<char> getoUnUdVals();
	
	std::vector<int> getDeltaEdges();
	std::vector<char> getDeltaVals();

	// given all new edges and their values 
	void mergeVectors(std::vector< std::vector<int> > &edgeVecsToMerge, std::vector< std::vector<char> > &valVecsToMerge, int srcID);
};

#endif
