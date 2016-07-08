#include <iostream>
#include <ctime>
#include <limits>
#include <unordered_set>
#include <queue>

#include "minset.h"
#include "../../include/aux.h"

// typedefs
typedef std::vector< std::vector<int> > intvec;
typedef std::vector< std::vector<char> > charvec;


// global variables
int deltaPtr = -1;
int oUnUdPtr = -1;
int currentID = -1;

std::unordered_set<char> currEvals;
std::priority_queue<MinSet, std::vector<MinSet>, compare> minEdges;

// function headers
void mergeVecs(intvec &edgesToMergs, charvec &valsToMerge, int srcID, std::vector<int> &deltaEdges,
		std::vector<char> &deltaVals, std::vector<int> &oUnUdEdges, std::vector<char> &oUnUdVals);

void updateMinSet(MinSet &minset, std::vector<int> &edges, std::vector<char> &vals);

void processMinSets(MinSet &srcMS, MinSet &tgtMS, std::vector<int> &srcDeltaEdges,
		std::vector<char> &srcDeltaVals, std::vector<int> &srcoUnUdEdges,
		std::vector<char> &srcoUnUdVals, std::vector<int> &srcEdgesToMerge,
		std::vector<char> &srcvalsToMerge, std::vector<int> &tgtEdgesToMerge,
		std::vector<char> &tgtValsTomerge);

void print_edges(intvec edgesToMerge, charvec valsToMerge, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << "ARR " << i << ": ";
		for (int j = 0; j < edgesToMerge[i].size(); j++)
			std::cout << "(" << edgesToMerge[i][j] << ", " << valsToMerge[i][j] << ")  ";

		std::cout << std::endl;
	}
}


int main()
{
	intvec edges{{100, 100, 200, 1700}, {2, 11, 17, 17, 25},
			{3, 12, 13, 18, 23}, {}, {1, 4, 11, 12}};
	charvec vals{{'a', 'd', 'a', 'b', 'c', 'e', 'd'}, {'d', 'a', 'b' ,'c', 'e'},
			{'d', 'a', 'e', 'c', 'c', 'b', 'a', 'a', 'd'}, {}, {'a', 'b', 'e', 'd'}};

	intvec deltaEdges{5};
	charvec deltaVals{5};
	intvec oldUnewUdeltaEdges{5};
	charvec oldUnewUdeltaVals{5};

	intvec edgeVecsToMerge{3};
	charvec valVecsToMerge{3};

	edgeVecsToMerge[0] = edges[0];
	valVecsToMerge[0] = vals[0];

	edgeVecsToMerge[1] = edges[1];
	valVecsToMerge[1] = vals[1];

	edgeVecsToMerge[2] = edges[2];
	valVecsToMerge[2] = vals[2];
	
	// SOUREC VERTEX
	int srcRowID = 0;

	print_edges(edgeVecsToMerge, valVecsToMerge, 3);

	Timer mergeTime;
	mergeTime.startTimer();

	mergeVecs(edgeVecsToMerge, valVecsToMerge, srcRowID, deltaEdges[srcRowID], deltaVals[srcRowID],
		oldUnewUdeltaEdges[srcRowID], oldUnewUdeltaVals[srcRowID]);

	mergeTime.endTimer();

	std::cout << "TIME: " << mergeTime.toString();

	return 0;
}


void mergeVecs(intvec &edgesToMerge, charvec &valsToMerge, int srcID, std::vector<int> &srcDeltaEdges,
		std::vector<char> &srcDeltaVals, std::vector<int> &srcoUnUdEdges,
		std::vector<char> &srcoUnUdVals)
{
	std::vector<MinSet> minsets{edgesToMerge.size()};

	int totTgtRowSize = 0;
	for (int i = 0; i < minsets.size(); i++)
	{
		minsets[i].setMinSetID(i);
		updateMinSet(minsets[i], edgesToMerge[i], valsToMerge[i]);

		if (i != srcID) {
			totTgtRowSize += edgesToMerge[i].size();
			minEdges.push(minsets[i]);
		}
	}

	srcDeltaEdges = std::vector<int>(totTgtRowSize, -1);
	srcDeltaVals = std::vector<char>(totTgtRowSize, ((char)63));

	srcoUnUdEdges = std::vector<int>(edgesToMerge[srcID].size() + totTgtRowSize, -1);
	srcoUnUdVals = std::vector<char>(edgesToMerge[srcID].size() + totTgtRowSize, ((char)63));

	MinSet src, tgt;
	while (1)
	{
		if (!minEdges.empty()) {
			tgt = minEdges.top();
			minEdges.pop();
		}

		int max = std::numeric_limits<int>::max();
		if (minsets[srcID].getCurrVID() == max && tgt.getCurrVID() == max) {
			break;
		}

		int indOfTgt = tgt.getMinSetID();
		processMinSets(minsets[srcID], tgt, srcDeltaEdges, srcDeltaVals, srcoUnUdEdges, srcoUnUdVals,
			edgesToMerge[srcID], valsToMerge[srcID], edgesToMerge[indOfTgt], valsToMerge[indOfTgt]);

		for (int k = 0; k < srcoUnUdEdges.size(); k++) 
			std::cout << "(" << srcoUnUdEdges[k]  << ", " << srcoUnUdVals[k] << ")  ";
		std::cout << std::endl;
	}
}


void updateMinSet(MinSet &minset, std::vector<int> &edges, std::vector<char> &vals)
{
	minset.setCurrVID(std::numeric_limits<int>::max());
	minset.clearEvalSet();

	for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++)
	{
		minset.setCurrVID(edges[i]);
		minset.addEval(vals[i]);
		minset.incPtr();
	}
}

void processMinSets(MinSet &srcMS, MinSet &tgtMS, std::vector<int> &srcDeltaEdges,
		std::vector<char> &srcDeltaVals, std::vector<int> &srcoUnUdEdges,
		std::vector<char> &srcoUnUdVals, std::vector<int> &srcEdgesToMerge,
		std::vector<char> &srcValsToMerge, std::vector<int> &tgtEdgesToMerge,
		std::vector<char> &tgtValsToMerge)
{
	// CURRENT VALUES
	std::cout << "SRC: " << srcMS.getCurrVID() << ",  TGT: " << tgtMS.getCurrVID() << std::endl;

	// case 1
	if (srcMS.getCurrVID() > tgtMS.getCurrVID())
	{
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> tgtVals = tgtMS.getEvals();
		for (std::unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
		{
			if (currEvals.find(*iter) == currEvals.end()) {
				oUnUdPtr++;
				if (oUnUdPtr < srcoUnUdEdges.size()) {
					srcoUnUdEdges[oUnUdPtr] = tgtMS.getCurrVID();
					srcoUnUdVals[oUnUdPtr] = *iter;
				}
				else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;

				deltaPtr++;
				if (deltaPtr < srcDeltaEdges.size()) {
					srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
					srcDeltaVals[deltaPtr] = *iter;
					currEvals.insert(*iter);
				}
				else std::cout << "ERROR: deltaPtr out of bounds" << std::endl;
			}
		}
		if (tgtEdgesToMerge.size() > 0) updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
		minEdges.push(tgtMS);

		return;
	}

	// case 2
	if (srcMS.getCurrVID() == tgtMS.getCurrVID())
	{
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> srcVals = srcMS.getEvals();
		std::unordered_set<char> tgtVals = tgtMS.getEvals();
		for (std::unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
		{
			if (srcVals.find(*iter) == srcVals.end()) {
				if (currEvals.find(*iter) == currEvals.end()) {
					oUnUdPtr++;
					if (oUnUdPtr < srcoUnUdEdges.size()) {
						srcoUnUdEdges[oUnUdPtr] = tgtMS.getCurrVID();
						srcoUnUdVals[oUnUdPtr] = *iter;
					}
					else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;

					deltaPtr++;
					if (deltaPtr < srcDeltaEdges.size()) {
						srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
						srcDeltaVals[deltaPtr] = *iter;
						currEvals.insert(*iter);
					}
					else std::cout << "ERROR: deltaPtr out of bounds" << std::endl;
 
				}
			}
		}
		if (tgtEdgesToMerge.size() > 0) updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
		if (tgtMS.getPtr() < tgtEdgesToMerge.size()) minEdges.push(tgtMS);

		return;
	}

	// case 3
	if (srcMS.getCurrVID() < tgtMS.getCurrVID())
	{
		if (currentID != srcMS.getCurrVID()) {
			currentID = srcMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> srcVals = srcMS.getEvals();
		for (std::unordered_set<char>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++)
		{
			if (currEvals.find(*iter) == currEvals.end()) {
				oUnUdPtr++;
				if (oUnUdPtr < srcoUnUdEdges.size()) {
					srcoUnUdEdges[oUnUdPtr] = srcMS.getCurrVID();
					srcoUnUdVals[oUnUdPtr] = *iter;
					currEvals.insert(*iter);
				}
				else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;
			}
		} 
	}
	if (srcEdgesToMerge.size() > 0) updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);

	return;
}


