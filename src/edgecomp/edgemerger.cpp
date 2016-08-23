#include "edgemerger.h"

// PUBLIC
EdgeMerger::EdgeMerger(short numRules)
{
	deltaPtr = -1;
	oUnUdPtr = -1;
	currID = -1;

	numEvals = 0;
	currEvals = new char[numRules];
}

EdgeMerger::~EdgeMerger()
{
	delete[] currEvals;
}

/**
 * given the vectors and vals to merge, as well as the ID of the source edges,
 * merge edges into a new list
 */
void EdgeMerger::mergeVectors(vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int srcID, short numRules)
{
	MinSet srcMS(numRules);
	srcMS.setMinSetID(0);
	updateMinSet(srcMS, edgeVecsToMerge[srcID], valVecsToMerge[srcID]);
	
	fillPriorityQueue(edgeVecsToMerge, valVecsToMerge, srcID, numRules);

	if (minEdges.empty()) {
		srcoUnUdEdges = edgeVecsToMerge[srcID];
		srcoUnUdVals = valVecsToMerge[srcID];

		cout << "MIN EDGES WAS EMPTY" << endl;

		return;
	}
	
    MinSet tgt(numRules);
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
void EdgeMerger::fillPriorityQueue(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID, short numRules)
{
	int totTgtRowSize = 0;
    for (int i = 1; i < edgeVecsToMerge.size(); i++)
    {
		if (!edgeVecsToMerge.empty()) {
			MinSet newminset(numRules);
			newminset.setMinSetID(i);
			updateMinSet(newminset, edgeVecsToMerge[i], valVecsToMerge[i]);

			totTgtRowSize += edgeVecsToMerge[i].size();
			minEdges.push(newminset);
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

bool EdgeMerger::findVal(char *evals, char val, int numVals)
{
	for (int i = 0; i < numVals; i++)
	{
		if (evals[i] == val) return true;
	}

	return false;
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
			numEvals = 0;
		}

		char *tgtVals = tgtMS.getEvals();
		for (int i = 0; i < tgtMS.getNumEvals(); i++)
		{
			if (!findVal(currEvals, tgtVals[i], numEvals)) {
				updateVector(tgtMS.getCurrVID(), tgtVals[i], srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
				updateVector(tgtMS.getCurrVID(), tgtVals[i], srcDeltaEdges, srcDeltaVals, deltaPtr);
				currEvals[numEvals] = tgtVals[i];
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 2
	if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
		if (currID != tgtMS.getCurrVID()) {
			currID = tgtMS.getCurrVID();
			numEvals = 0;
		}

		char *srcVals = srcMS.getEvals();
		char *tgtVals = tgtMS.getEvals();
		for (int i = 0; i < tgtMS.getNumEvals(); i++)
		{
			if (!findVal(srcVals, tgtVals[i], srcMS.getNumEvals())) {
				if (!findVal(currEvals, tgtVals[i], numEvals)) {
					updateVector(tgtMS.getCurrVID(), tgtVals[i], srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
					updateVector(tgtMS.getCurrVID(), tgtVals[i], srcDeltaEdges, srcDeltaVals, deltaPtr);
					currEvals[numEvals] = tgtVals[i];
                }
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 3
	if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
		if (currID != srcMS.getCurrVID()) {
			currID = srcMS.getCurrVID();
			numEvals = 0;
		}

		char *srcVals = srcMS.getEvals();
		for (int i = 0; i < srcMS.getNumEvals(); i++)
		{
			if (!findVal(currEvals, srcVals[i], numEvals)) {
				updateVector(srcMS.getCurrVID(), srcVals[i], srcoUnUdEdges, srcoUnUdVals, oUnUdPtr);
				currEvals[numEvals] = srcVals[i];
            }
        }
        updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
        minEdges.push(tgtMS);

        return;
    }
}

void EdgeMerger::updateVector(int vid, char val, vector<int> &edges, vector<char> &vals, int &ptr)
{
	ptr++;
	edges[ptr] = vid;
	vals[ptr] = val;
}
