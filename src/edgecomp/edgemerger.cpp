#include "edgemerger.h"

// PUBLIC
EdgeMerger::EdgeMerger()
{
	deltaPtr = -1;
	oUnUdPtr = -1;
	currID = -1;
}

/**
 * given the vectors and vals to merge, as well as the ID of the source edges,
 * merge edges into a new list
 */
void EdgeMerger::mergeVectors(vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int srcID)
{
	MinSet srcMS;
	srcMS.setMinSetID(0);
	updateMinSet(srcMS, edgeVecsToMerge[srcID], valVecsToMerge[srcID]);
	
	fillPriorityQueue(edgeVecsToMerge, valVecsToMerge, srcID);

	if (minEdges.empty()) {
		srcoUnUdEdges = edgeVecsToMerge[srcID];
		srcoUnUdVals = valVecsToMerge[srcID];

		return;
	}
	
    MinSet tgt;
    int max = std::numeric_limits<int>::max();
    while (1)
    {
        if (!minEdges.empty()) {
            tgt = minEdges.top();
            minEdges.pop();
        }

        if (srcMS.getCurrVID() == max && tgt.getCurrVID() == max) {
            break;
        }

        int indOfTgt = tgt.getMinSetID();
        processMinSets(srcMS, tgt, edgeVecsToMerge[srcID], valVecsToMerge[srcID], edgeVecsToMerge[indOfTgt], valVecsToMerge[indOfTgt]);

    }

    removeExtraSpace();

//    cout << "oldUnewUdelta AFTER update  ->  ";
//    for (int k = 0; k < srcoUnUdEdges.size(); k++)
//        cout << "(" << srcoUnUdEdges[k]  << ", " << (short)srcoUnUdVals[k] << ")  ";
//    cout << endl;
//    cout << "delta AFTER update -> ";
//    for (int l = 0; l < srcDeltaEdges.size(); l++)
//        cout << "(" << srcDeltaEdges[l] << ", " << (short)srcDeltaVals[l] << ")  ";
//    cout << endl << std::endl;
}


// PRIVATE
/**
 * given the vectors of edges to merge, create a priority queue to quickly find the edge with the lowest 
 * dest vertex
 */
void EdgeMerger::fillPriorityQueue(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID)
{
	MinSet newminset;
	int totTgtRowSize = 0;
    for (int i = 1; i < edgeVecsToMerge.size(); i++)
    {
		if (!edgeVecsToMerge[i].empty()) {
			newminset.setMinSetID(i);
			updateMinSet(newminset, edgeVecsToMerge[i], valVecsToMerge[i]);

			totTgtRowSize += edgeVecsToMerge[i].size();
			minEdges.push(newminset);
			newminset.resetPtr();
		}
    }

    srcDeltaEdges.reserve(totTgtRowSize);
    srcDeltaVals.reserve(totTgtRowSize);

    srcoUnUdEdges.reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
    srcoUnUdVals.reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
}

/**
 * remove the excess space created when duplicate values were removed
 */
void EdgeMerger::removeExtraSpace()
{
	srcoUnUdEdges = vector<int>(srcoUnUdEdges.begin(), srcoUnUdEdges.begin() + oUnUdPtr + 1);
	srcoUnUdVals = vector<char>(srcoUnUdVals.begin(), srcoUnUdVals.begin() + oUnUdPtr + 1);

	srcDeltaEdges = vector<int>(srcDeltaEdges.begin(), srcDeltaEdges.begin() + deltaPtr + 1);
	srcDeltaVals = vector<char>(srcDeltaVals.begin(), srcDeltaVals.begin() + deltaPtr + 1);
}

/**
 * for the given minset, find the next minimum value and any corresponding values
 */
void EdgeMerger::updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals)
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

/**
 * compare the next smallest target minset with the source minset to determine which vector to update
 */
void EdgeMerger::processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge)
{
	// case 1
	if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
		if (currID != tgtMS.getCurrVID()) {
			currID = tgtMS.getCurrVID();
			currEvals.clear();
		}

        unordered_set<char> &tgtVals = tgtMS.getEvals();
        for (unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
		{
            if (currEvals.find(*iter) == currEvals.end()) {
				updateVector(tgtMS.getCurrVID(), *iter, srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
				updateVector(tgtMS.getCurrVID(), *iter, srcDeltaEdges, srcDeltaVals, deltaPtr);
				currEvals.insert(*iter);
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
    }

	// case 2
	else if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
		if (currID != tgtMS.getCurrVID()) {
			currID = tgtMS.getCurrVID();
			currEvals.clear();
		}

        unordered_set<char> &srcVals = srcMS.getEvals();
        unordered_set<char> &tgtVals = tgtMS.getEvals();
        for (unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
		{
            if (srcVals.find(*iter) == srcVals.end()) {
                if (currEvals.find(*iter) == currEvals.end()) {
					updateVector(tgtMS.getCurrVID(), *iter, srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
					updateVector(tgtMS.getCurrVID(), *iter, srcDeltaEdges, srcDeltaVals, deltaPtr);
					currEvals.insert(*iter);
                }
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
    }

	// case 3
	else if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
		if (currID != srcMS.getCurrVID()) {
			currID = srcMS.getCurrVID();
			currEvals.clear();
		}

        unordered_set<char> &srcVals = srcMS.getEvals();
        for (unordered_set<char>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++)
		{
            if (currEvals.find(*iter) == currEvals.end()) {
				updateVector(srcMS.getCurrVID(), *iter, srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
				currEvals.insert(*iter);
            }
        }
        updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
    }

	minEdges.push(tgtMS);
}

void EdgeMerger::updateVector(int vid, char val, vector<int> &edges, vector<char> &vals, int &ptr)
{
	ptr++;
	edges[ptr] = vid;
	vals[ptr] = val;
}
