#include "minset.h"
#include "merge.h"

using std::vector;
using std::unordered_set;

// TODO: Remove extra space in vecs after merge
// TODO: Make into class to pass updated vectors back to "compute.cpp"
// TODO: Do for more than just one iteration


// GLOBAL VARS
int deltaPtr = -1;
int oUnUdPtr = -1;
int currentID = -1;

unordered_set<char> currEvals;
std::priority_queue<MinSet, vector<MinSet>, compare> minEdges;

// FUNCTION HEADERS
void mergeVecs(vector< vector<int> > &edgesToMergs, vector< vector<char> > &valsToMerge, int srcID, vector<int> &deltaEdges,
		vector<char> &deltaVals, vector<int> &oUnUdEdges, vector<char> &oUnUdVals);

void removeExtraSpace(vector<int> &oUnUdEdges, vector<char> &oUnUdVals,
		vector<int> &deltaEdges, vector<char> &deltaVals);

void updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals);

void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcDeltaEdges,
		vector<char> &srcDeltaVals, vector<int> &srcoUnUdEdges,
		vector<char> &srcoUnUdVals, vector<int> &srcEdgesToMerge,
		vector<char> &srcvalsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsTomerge);

void print_edges(vector< vector<int> > &edges, vector< vector<char> > &vals)
{
	for (int i = 0; i < edges.size(); i++)
	{
		std::cout << "ROW " << i << ": ";
		for (int j = 0; j < edges[i].size(); j++)
			std::cout << "(" << edges[i][j] << ", " << vals[i][j] << ")  ";

		std::cout << std::endl;
	}
}


int main()
{
	vector< vector<int> > edges{{100, 100, 200, 1700}, {2, 11, 17, 17, 25},
			{3, 12, 13, 18, 23}, {}, {1, 4, 11, 12}};
	vector< vector<char> > vals{{'a', 'd', 'a', 'b', 'c', 'e', 'd'}, {'d', 'a', 'b' ,'c', 'e'},
			{'d', 'a', 'e', 'c', 'c', 'b', 'a', 'a', 'd'}, {}, {'a', 'b', 'e', 'd'}};


	vector< vector<int> > deltaEdges{5};
	vector< vector<char> > deltaVals{5};
	vector< vector<int> > oldUnewUdeltaEdges{5};
	vector< vector<char> > oldUnewUdeltaVals{5};

	vector< vector<int> > edgeVecsToMerge{3};
	vector< vector<char> > valVecsToMerge{3};

	edgeVecsToMerge[0] = edges[0];
	valVecsToMerge[0] = vals[0];

	edgeVecsToMerge[1] = edges[1];
	valVecsToMerge[1] = vals[1];

	edgeVecsToMerge[2] = edges[2];
	valVecsToMerge[2] = vals[2];

	print_edges(edgeVecsToMerge, valVecsToMerge);
	
	
	// SOUREC VERTEX
	int srcID = 0;

	mergeVecs(edgeVecsToMerge, valVecsToMerge, srcID, deltaEdges[srcID], deltaVals[srcID],
		oldUnewUdeltaEdges[srcID], oldUnewUdeltaVals[srcID]);

	std::cout << std::endl << "oUnUd Edges: ";
	for (int i = 0; i < oldUnewUdeltaEdges[0].size(); i++)
		std::cout << "(" << oldUnewUdeltaEdges[0][i] << ", " << oldUnewUdeltaVals[0][i] << ")  ";
	std::cout << std::endl;

	std::cout << "delta Edges: ";
	for (int j = 0; j < deltaEdges[0].size(); j++)
		std::cout << "(" << deltaEdges[0][j] << ", " << deltaVals[0][j] << ")  ";
	std::cout << std::endl;
	

	// TEMP while iterative
	// once using threads will need to make this file a class
	oUnUdPtr = -1;
	deltaPtr = -1;
	currentID = -1;
	currEvals.clear();
	while (!minEdges.empty()) minEdges.pop();
}


void mergeVecs(vector< vector<int> > &edgesToMerge, vector< vector<char> > &valsToMerge, int srcID, vector<int> &srcDeltaEdges, vector<char> &srcDeltaVals, vector<int> &srcoUnUdEdges, vector<char> &srcoUnUdVals)
{
//	vector<MinSet> minsets{edgesToMerge.size()};

	MinSet srcMS;
	srcMS.setMinSetID(0);
	updateMinSet(srcMS, edgesToMerge[srcID], valsToMerge[srcID]);

	MinSet newminset;
	int totTgtRowSize = 0;
	for (int i = 1; i < edgesToMerge.size(); i++)
	{
		newminset.setMinSetID(i);
		updateMinSet(newminset, edgesToMerge[i], valsToMerge[i]);

		totTgtRowSize += edgesToMerge[i].size();
		minEdges.push(newminset);
	}

	srcDeltaEdges.reserve(totTgtRowSize);
	srcDeltaVals.reserve(totTgtRowSize);

	srcoUnUdEdges.reserve(totTgtRowSize + edgesToMerge[0].size());
	srcoUnUdVals.reserve(totTgtRowSize + edgesToMerge[0].size());

	MinSet tgt;
	while (1)
	{
		if (!minEdges.empty()) {
			tgt = minEdges.top();
			minEdges.pop();
		}

		int max = std::numeric_limits<int>::max();
		if (srcMS.getCurrVID() == max && tgt.getCurrVID() == max) {
			break;
		}

		int indOfTgt = tgt.getMinSetID();
		processMinSets(srcMS, tgt, srcDeltaEdges, srcDeltaVals, srcoUnUdEdges, srcoUnUdVals,
			edgesToMerge[srcID], valsToMerge[srcID], edgesToMerge[indOfTgt], valsToMerge[indOfTgt]);

	}

	removeExtraSpace(srcoUnUdEdges, srcoUnUdVals, srcDeltaEdges, srcDeltaVals);
}

void removeExtraSpace(vector<int> &oUnUdEdges, vector<char> &oUnUdVals,
		vector<int> &deltaEdges, vector<char> &deltaVals)
{
	oUnUdEdges = vector<int>(oUnUdEdges.begin(), oUnUdEdges.begin() + oUnUdPtr + 1);
	oUnUdVals = vector<char>(oUnUdVals.begin(), oUnUdVals.begin() + oUnUdPtr + 1);

	deltaEdges = vector<int>(deltaEdges.begin(), deltaEdges.begin() + deltaPtr + 1);
	deltaVals = vector<char>(deltaVals.begin(), deltaVals.begin() + deltaPtr + 1);
}

void updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals)
{
	minset.setCurrVID(std::numeric_limits<int>::max());
	minset.clearEvalSet();

	for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++) {
		minset.setCurrVID(edges[i]);
		minset.addEval(vals[i]);
		minset.incPtr();
	}
}

void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcDeltaEdges,
		vector<char> &srcDeltaVals, vector<int> &srcoUnUdEdges,
		vector<char> &srcoUnUdVals, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge)
{
	// case 1
	if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		unordered_set<char> tgtVals = tgtMS.getEvals();
		for (unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++) {
			if (currEvals.find(*iter) == currEvals.end()) {
				oUnUdPtr++;
				if (oUnUdPtr < srcoUnUdEdges.capacity()) {
					srcoUnUdEdges[oUnUdPtr] = tgtMS.getCurrVID();
					srcoUnUdVals[oUnUdPtr] = *iter;
				}
				else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;

				deltaPtr++;
				if (deltaPtr < srcDeltaEdges.capacity()) {
					srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
					srcDeltaVals[deltaPtr] = *iter;
					currEvals.insert(*iter);
				}
				else std::cout << "ERROR: deltaPtr out of bounds" << std::endl;
			}
		}
		updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
		minEdges.push(tgtMS);

		return;
	}

	// case 2
	if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
		if (currentID != tgtMS.getCurrVID()) {
			currentID = tgtMS.getCurrVID();
			currEvals.clear();
		}

		unordered_set<char> srcVals = srcMS.getEvals();
		unordered_set<char> tgtVals = tgtMS.getEvals();
		for (unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++) {
			if (srcVals.find(*iter) == srcVals.end()) {
				if (currEvals.find(*iter) == currEvals.end()) {
					oUnUdPtr++;
					if (oUnUdPtr < srcoUnUdEdges.capacity()) {
						srcoUnUdEdges[oUnUdPtr] = tgtMS.getCurrVID();
						srcoUnUdVals[oUnUdPtr] = *iter;
					}
					else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;

					deltaPtr++;
					if (deltaPtr < srcDeltaEdges.capacity()) {
						srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
						srcDeltaVals[deltaPtr] = *iter;
						currEvals.insert(*iter);
					}
					else std::cout << "ERROR: deltaPtr out of bounds" << std::endl;
 
				}
			}
		}
		updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
		minEdges.push(tgtMS);

		return;
	}

	// case 3
	if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
		if (currentID != srcMS.getCurrVID()) {
			currentID = srcMS.getCurrVID();
			currEvals.clear();
		}

		unordered_set<char> srcVals = srcMS.getEvals();
		for (unordered_set<char>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++) {
			if (currEvals.find(*iter) == currEvals.end()) {
				oUnUdPtr++;
				if (oUnUdPtr < srcoUnUdEdges.capacity()) {
					srcoUnUdEdges[oUnUdPtr] = srcMS.getCurrVID();
					srcoUnUdVals[oUnUdPtr] = *iter;
					currEvals.insert(*iter);
				}
				else std::cout << "ERROR: oUnUdPtr out of bounds" << std::endl;
			}
		} 
		updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
		minEdges.push(tgtMS);

		return;
	}
}


