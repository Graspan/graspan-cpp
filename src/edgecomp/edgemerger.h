#ifndef EDGEMERGER_H
#define EDGEMERGER_H

#include <iostream>
#include <ctime>
#include <limits>
#include <unordered_set>
#include <queue>

#include "../datastructures/minset.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"


class EdgeMerger
{
	int deltaPtr;
	int oUnUdPtr;
	int currID;

	std::unordered_set<char> currEvals;
	std::priority_queue<MinSet, vector<MinSet>, compare> minEdges;

	vector<int> srcoUnUdEdges;
	vector<char> srcoUnUdVals;

	vector<int> srcDeltaEdges;
	vector<char> srcDeltaVals;


	// FUNCTIONS
	void removeExtraSpace();

	void updateMinSet(MinSet &minset, vector<int> &edges, std::vector<char> &vals);

	void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, std::vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge);

	public:
	// constructor
	EdgeMerger();

	// getters
	vector<int> getoUnUdEdges();
	vector<char> getoUnUdVals();
	
	vector<int> getDeltaEdges();
	vector<char> getDeltaVals();

	// given all new edges and their values 
	void mergeVectors(vector< std::vector<int> > &edgeVecsToMerge, std::vector< std::vector<char> > &valVecsToMerge, int srcID);
};

#endif
