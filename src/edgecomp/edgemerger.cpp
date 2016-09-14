#include "edgemerger.h"

// PUBLIC
EdgeMerger::EdgeMerger()
{
	deltaPtr = -1;
	oUnUdPtr = -1;
	currID = -1;

	srcDeltaEdges = std::make_shared<vector<int>>(vector<int>());
	srcDeltaVals = std::make_shared<vector<char>>(vector<char>());

	srcoUnUdEdges = std::make_shared<vector<int>>(vector<int>());
	srcoUnUdVals = std::make_shared<vector<char>>(vector<char>());
}

/**
 * given the vectors and vals to merge, as well as the ID of the source edges,
 * merge edges into a new list
 */
void EdgeMerger::mergeVectors(int vertInd, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int srcID)
{
	MinSet srcMS;				// initialize a MinSet for the source vertex
	srcMS.setMinSetID(0);
	updateMinSet(srcMS, edgeVecsToMerge[srcID], valVecsToMerge[srcID]);		// initialize the info of the source MinSet
	
	fillPriorityQueue(edgeVecsToMerge, valVecsToMerge, srcID);
	
    MinSet tgt;
    int max = std::numeric_limits<int>::max();
    while (1)
    {
        if (!minEdges.empty()) {
            tgt = minEdges.top();		// get reference to the minset with the smallest vertex value
            minEdges.pop();
        }

        if (srcMS.getCurrVID() == max && tgt.getCurrVID() == max) {
            break;
        }

        int indOfTgt = tgt.getMinSetID();
        processMinSets(srcMS, tgt, edgeVecsToMerge[srcID], valVecsToMerge[srcID], edgeVecsToMerge[indOfTgt], valVecsToMerge[indOfTgt]);

    }

	if (vertInd == 0) {	
		cout << "== SRCOUNUD ===\n";
		if (srcoUnUdEdges->empty()) cout << "srcoUnUdEdges empty...\n\n";
		else {
			for (int i = 0; i < srcoUnUdEdges->size(); i++)
				cout << "(" << srcoUnUdEdges->at(i) << ", " << (short)srcoUnUdVals->at(i) << ")  ";

			cout << endl << endl;
		}
	}
    removeExtraSpace();
}


// PRIVATE
/**
 * fill the minEdges priority_queue with the lowest value in each vector. Find the total number of new edges and reserve
 * space in the vectors accordingly
 */
void EdgeMerger::fillPriorityQueue(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID)
{
	MinSet newminset;
	int totTgtRowSize = 0;
    for (int i = 1; i < edgeVecsToMerge.size(); i++)
    {
		newminset.setMinSetID(i);
		updateMinSet(newminset, edgeVecsToMerge[i], valVecsToMerge[i]);

		totTgtRowSize += edgeVecsToMerge[i].size();
		minEdges.push(newminset);
		newminset.resetPtr();
    }

    srcDeltaEdges->reserve(totTgtRowSize);
    srcDeltaVals->reserve(totTgtRowSize);

    srcoUnUdEdges->reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
    srcoUnUdVals->reserve(edgeVecsToMerge[srcID].size() + totTgtRowSize);
}

/**
 * remove the excess space created when duplicate values were removed
 */
void EdgeMerger::removeExtraSpace()
{
	// TODO: this happens no matter what right now. Use a conditional statement to stop this from
	// happening every time and avoid excessive copying!
	/*
	vector<int> *tempoUnUdEdges = new vector<int>(srcoUnUdEdges->begin(), srcoUnUdEdges->begin() + oUnUdPtr + 1);
	vector<int> *tempDeltaEdges = new vector<int>(srcDeltaEdges->begin(), srcDeltaEdges->begin() + deltaPtr + 1);
	vector<char> *tempoUnUdVals = new vector<char>(srcoUnUdVals->begin(), srcoUnUdVals->begin() + oUnUdPtr + 1);
	vector<char> *tempDeltaVals = new vector<char>(srcDeltaVals->begin(), srcDeltaVals->begin() + deltaPtr + 1);

	vector<int> *tempe = srcoUnUdEdges;
	vector<char> *tempv = srcoUnUdVals;
	vector<int> *tempde = srcDeltaEdges;
	vector<char> *tempdv = srcDeltaVals;

	srcoUnUdEdges = tempoUnUdEdges;
	srcoUnUdVals = tempoUnUdVals;
	srcDeltaEdges = tempDeltaEdges;
	srcDeltaVals = tempDeltaVals;

	delete tempe;
	delete tempv;
	delete tempde;
	delete tempdv;
	*/
}

/**
 * for the given minset, find the next minimum value and any corresponding values
 */
void EdgeMerger::updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals)
{
	minset.setCurrVID(std::numeric_limits<int>::max());		// set the VID as the max so all values will be smaller
	minset.clearEvalSet();		// because it is a new vertex, get rid of any values in the edge value set

	for (int i = minset.getPtr(); i < edges.size() && edges[i] <= minset.getCurrVID(); i++)		// find all edge values
	{																							// associated with a 
		minset.setCurrVID(edges[i]);															// specific edge value
		minset.addEval(vals[i]);																// and store them in the
		minset.incPtr();																		// minset
	}
}

/**
 * compare the next smallest target minset with the source minset to determine which vector to update
 */
void EdgeMerger::processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge)
{
	// case 1 - the target vertexID is smaller than the source vertexID
	if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
		if (currID != tgtMS.getCurrVID()) {
			currID = tgtMS.getCurrVID();
			currEvals.clear();
		}

        unordered_set<char> &tgtVals = tgtMS.getEvals();
        for (unordered_set<char>::iterator iter = tgtVals.begin(); iter != tgtVals.end(); iter++)
		{
            if (currEvals.find(*iter) == currEvals.end()) {		// check if an edge with that edge value has already been added
				oUnUdPtr++;
				deltaPtr++;
				srcoUnUdEdges->push_back(tgtMS.getCurrVID());
				srcDeltaEdges->push_back(tgtMS.getCurrVID());
				srcoUnUdVals->push_back(*iter);
				srcDeltaVals->push_back(*iter);
				currEvals.insert(*iter);				// insert edge value into currEvals to mark as already used
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 2 - target vertexID and source vertexID are equal
	if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
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
					oUnUdPtr++;
					deltaPtr++;
					srcoUnUdEdges->push_back(tgtMS.getCurrVID());
					srcDeltaEdges->push_back(tgtMS.getCurrVID());
					srcoUnUdVals->push_back(*iter);
					srcDeltaVals->push_back(*iter);
					currEvals.insert(*iter);
                }
            }
        }
        updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 3 - source vertexID is less than target vertexID
	if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
		if (currID != srcMS.getCurrVID()) {
			currID = srcMS.getCurrVID();
			currEvals.clear();
		}

        unordered_set<char> &srcVals = srcMS.getEvals();
        for (unordered_set<char>::iterator iter = srcVals.begin(); iter != srcVals.end(); iter++)
		{
            if (currEvals.find(*iter) == currEvals.end()) {
				oUnUdPtr++;
				srcoUnUdEdges->push_back(srcMS.getCurrVID());
				srcoUnUdVals->push_back(*iter);
				currEvals.insert(*iter);															// because not new
            }
        }
        updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
        minEdges.push(tgtMS);

        return;
    }
}

/**
 * increment the pointer, then add the vertexID and the edge value into the vector
 */
void EdgeMerger::updateVector(int vid, char val, int &ptr, char flag)
{
	vector<int> &edges = (flag == 'o') ? *(srcoUnUdEdges) : *(srcDeltaEdges);
	vector<char> &vals = (flag =='o') ? *(srcoUnUdVals) : *(srcDeltaVals);

	ptr++;
	edges[ptr] = vid;
	vals[ptr] = val;
}
