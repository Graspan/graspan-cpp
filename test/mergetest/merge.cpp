#include "../../../include/minset.h"
#include "../../../include/merge.h"
#include "../../../include/timer.h"

// TODO: Remove extra space in vecs after merge
// TODO: Make into class to pass updated vectors back to "compute.cpp"
// TODO: Do for more than just one iteration


// GLOBAL VARS
int deltaPtr = -1;
int oUnUdPtr = -1;
int currentID = -1;

std::unordered_set<char> currEvals;
std::priority_queue<MinSet, std::vector<MinSet>, compare> minEdges;

// FUNCTION HEADERS
void mergeVecs(std::vector< std::vector<int> > &edgesToMergs, std::vector< std::vector<char> > &valsToMerge, int srcID, std::vector<int> &deltaEdges,
		std::vector<char> &deltaVals, std::vector<int> &oUnUdEdges, std::vector<char> &oUnUdVals);

void removeExtraSpace(std::vector<int> &oUnUdEdges, std::vector<char> &oUnUdVals,
		std::vector<int> &deltaEdges, std::vector<char> &deltaVals);

void updateMinSet(MinSet &minset, std::vector<int> &edges, std::vector<char> &vals);

void processMinSets(MinSet &srcMS, MinSet &tgtMS, std::vector<int> &srcDeltaEdges,
		std::vector<char> &srcDeltaVals, std::vector<int> &srcoUnUdEdges,
		std::vector<char> &srcoUnUdVals, std::vector<int> &srcEdgesToMerge,
		std::vector<char> &srcvalsToMerge, std::vector<int> &tgtEdgesToMerge,
		std::vector<char> &tgtValsTomerge);



void vecMerge(std::vector< std::vector<int> > &edgeVecsToMerge, std::vector< std::vector<char> > &valVecsToMerge, int srcID)
{
//	std::vector< std::vector<int> > edges{{100, 100, 200, 1700}, {2, 11, 17, 17, 25},
//			{3, 12, 13, 18, 23}, {}, {1, 4, 11, 12}};
//	std::vector< std::vector<char> > vals{{'a', 'd', 'a', 'b', 'c', 'e', 'd'}, {'d', 'a', 'b' ,'c', 'e'},
//			{'d', 'a', 'e', 'c', 'c', 'b', 'a', 'a', 'd'}, {}, {'a', 'b', 'e', 'd'}};
//
	std::vector< std::vector<int> > deltaEdges{5};
	std::vector< std::vector<char> > deltaVals{5};
	std::vector< std::vector<int> > oldUnewUdeltaEdges{5};
	std::vector< std::vector<char> > oldUnewUdeltaVals{5};
//
//	std::vector< std::vector<int> > edgeVecsToMerge{3};
//	std::vector< std::vector<char> > valVecsToMerge{3};
//
//	edgeVecsToMerge[0] = edges[0];
//	valVecsToMerge[0] = vals[0];
//
//	edgeVecsToMerge[1] = edges[1];
//	valVecsToMerge[1] = vals[1];
//
//	edgeVecsToMerge[2] = edges[2];
//	valVecsToMerge[2] = vals[2];
//	
//	// SOUREC VERTEX
//	int srcRowID = 0;
//
//	print_edges(edgeVecsToMerge, valVecsToMerge, 3);
//
	Timer mergeTime;
	mergeTime.startTimer();

	mergeVecs(edgeVecsToMerge, valVecsToMerge, srcID, deltaEdges[srcID], deltaVals[srcID],
		oldUnewUdeltaEdges[srcID], oldUnewUdeltaVals[srcID]);

	mergeTime.endTimer();

	std::cout << "MERGE TIME: " << mergeTime.toString() << std::endl << std::endl;

	// TEMP while iterative
	// once using threads will need to make this file a class
	oUnUdPtr = -1;
	deltaPtr = -1;
	currentID = -1;
	currEvals.clear();
	while (!minEdges.empty()) minEdges.pop();
}


void mergeVecs(std::vector< std::vector<int> > &edgesToMerge, std::vector< std::vector<char> > &valsToMerge, int srcID, std::vector<int> &srcDeltaEdges,
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

	}

	removeExtraSpace(srcoUnUdEdges, srcoUnUdVals, srcDeltaEdges, srcDeltaVals);

	std::cout << "oldUnewUdelta AFTER update  ->  ";
	for (int k = 0; k < srcoUnUdEdges.size(); k++) 
		std::cout << "(" << srcoUnUdEdges[k]  << ", " << srcoUnUdVals[k] << ")  ";
	std::cout << std::endl;
	std::cout << "delta AFTER update -> ";
	for (int l = 0; l < srcDeltaEdges.size(); l++)
		std::cout << "(" << srcDeltaEdges[l] << ", " << srcDeltaVals[l] << ")  ";
	std::cout << std::endl;
}

void removeExtraSpace(std::vector<int> &oUnUdEdges, std::vector<char> &oUnUdVals,
		std::vector<int> &deltaEdges, std::vector<char> &deltaVals)
{
	oUnUdEdges = std::vector<int>(oUnUdEdges.begin(), oUnUdEdges.begin() + oUnUdPtr + 1);
	oUnUdVals = std::vector<char>(oUnUdVals.begin(), oUnUdVals.begin() + oUnUdPtr + 1);

	if (deltaPtr >= 0) {
		deltaEdges = std::vector<int>(deltaEdges.begin(), deltaEdges.begin() + deltaPtr + 1);
		deltaVals = std::vector<char>(deltaVals.begin(), deltaVals.begin() + deltaPtr + 1);
	}
}

void updateMinSet(MinSet &minset, std::vector<int> &edges, std::vector<char> &vals)
{
	minset.setCurrVID(std::numeric_limits<int>::max());
	minset.clearEvalSet();

	for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++) {
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
	// case 1
	if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> tgtVals = tgtMS.getEvals();
		for (std::unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++) {
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
	if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> srcVals = srcMS.getEvals();
		std::unordered_set<char> tgtVals = tgtMS.getEvals();
		for (std::unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++) {
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
		minEdges.push(tgtMS);

		return;
	}

	// case 3
	if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
		if (currentID != srcMS.getCurrVID()) {
			currentID = srcMS.getCurrVID();
			currEvals.clear();
		}

		std::unordered_set<char> srcVals = srcMS.getEvals();
		for (std::unordered_set<char>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++) {
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
		if (srcEdgesToMerge.size() > 0) updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
		minEdges.push(tgtMS);

		return;
	}
}


