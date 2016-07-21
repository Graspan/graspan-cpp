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
	void fillPriorityQueue(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID);

	void removeExtraSpace();

	void updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals);

	void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge);

	void updateVector(int vid, char val, vector<int> &edges, vector<char> &vals, int &ptr);

	public:
	// constructor
	EdgeMerger();

	// getters
	vector<int> &getoUnUdEdges();
	vector<char> &getoUnUdVals();
	
	vector<int> &getDeltaEdges();
	vector<char> &getDeltaVals();

	int getNumNewEdges();

	// given all new edges and their values, merge with the source creating a vector of old U new edges
	// and only new edges
	void mergeVectors(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID);
};

#endif
