#include "edgemerger.h"

// PUBLIC
EdgeMerger::EdgeMerger()
{
	deltaPtr = -1;
	oUnUdPtr = -1;
	currID = -1;
}

// getters
vector<int> EdgeMerger::getoUnUdEdges() { return srcoUnUdEdges; }
vector<char> EdgeMerger::getoUnUdVals() { return srcoUnUdVals; }

vector<int> EdgeMerger::getDeltaEdges() { return srcDeltaEdges; }
vector<char> EdgeMerger::getDeltaVals() { return srcDeltaVals; }

void EdgeMerger::mergeVectors(vector< std::vector<int> > &edgeVecsToMerge,
		vector< std::vector<char> > &valVecsToMerge, int srcID)
{
	Timer mergeTime;
	mergeTime.startTimer();

	vector<MinSet> minsets(edgeVecsToMerge.size());
	
	int totTgtRowSize = 0;
    for (int i = 0; i < minsets.size(); i++)
    {
        minsets[i].setMinSetID(i);
        updateMinSet(minsets[i], edgeVecsToMerge[i], valVecsToMerge[i]);

        if (i != srcID) {
            totTgtRowSize += edgeVecsToMerge[i].size();
            minEdges.push(minsets[i]);
        }
    }

    srcDeltaEdges = vector<int>(totTgtRowSize, -1);
    srcDeltaVals = vector<char>(totTgtRowSize, ((char)63));

    srcoUnUdEdges = vector<int>(edgeVecsToMerge[srcID].size() + totTgtRowSize, -1);
    srcoUnUdVals = vector<char>(edgeVecsToMerge[srcID].size() + totTgtRowSize, ((char)63));

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
        processMinSets(minsets[srcID], tgt, edgeVecsToMerge[srcID], valVecsToMerge[srcID], edgeVecsToMerge[indOfTgt], valVecsToMerge[indOfTgt]);

    }

    removeExtraSpace();

    cout << "oldUnewUdelta AFTER update  ->  ";
    for (int k = 0; k < srcoUnUdEdges.size(); k++)
        cout << "(" << srcoUnUdEdges[k]  << ", " << srcoUnUdVals[k] << ")  ";
    cout << endl;
    cout << "delta AFTER update -> ";
    for (int l = 0; l < srcDeltaEdges.size(); l++)
        cout << "(" << srcDeltaEdges[l] << ", " << srcDeltaVals[l] << ")  ";
    cout << endl << std::endl;

	mergeTime.endTimer();
}


// PRIVATE
void EdgeMerger::removeExtraSpace()
{
	srcoUnUdEdges = vector<int>(srcoUnUdEdges.begin(), srcoUnUdEdges.begin() + oUnUdPtr + 1);
	srcoUnUdVals = vector<char>(srcoUnUdVals.begin(), srcoUnUdVals.begin() + oUnUdPtr + 1);

	if (deltaPtr >= 0) {
		srcDeltaEdges = vector<int>(srcDeltaEdges.begin(), srcDeltaEdges.begin() + deltaPtr + 1);
        srcDeltaVals = vector<char>(srcDeltaVals.begin(), srcDeltaVals.begin() + deltaPtr + 1);
	}
}

void EdgeMerger::updateMinSet(MinSet &minset, vector<int> &edges, std::vector<char> &vals)
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

void EdgeMerger::processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, std::vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge)
{
	// case 1
	if (srcMS.getCurrVID() > tgtMS.getCurrVID()) {
        if (currID != tgtMS.getCurrVID()) {
            currID = tgtMS.getCurrVID();
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
                else cout << "ERROR: oUnUdPtr out of bounds" << endl;

                deltaPtr++;
                if (deltaPtr < srcDeltaEdges.size()) {
                    srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
                    srcDeltaVals[deltaPtr] = *iter;
                    currEvals.insert(*iter);
                }
                else cout << "ERROR: deltaPtr out of bounds" << endl;
            }
        }
        if (tgtEdgesToMerge.size() > 0) updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 2
	if (srcMS.getCurrVID() == tgtMS.getCurrVID()) {
        if (currID != tgtMS.getCurrVID()) {
            currID = tgtMS.getCurrVID();
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
                    else cout << "ERROR: oUnUdPtr out of bounds" << endl;

                    deltaPtr++;
                    if (deltaPtr < srcDeltaEdges.size()) {
                        srcDeltaEdges[deltaPtr] = tgtMS.getCurrVID();
                        srcDeltaVals[deltaPtr] = *iter;
                        currEvals.insert(*iter);
                    }
                    else cout << "ERROR: deltaPtr out of bounds" << endl;

                }
            }
        }
        if (tgtEdgesToMerge.size() > 0) updateMinSet(tgtMS, tgtEdgesToMerge, tgtValsToMerge);
        minEdges.push(tgtMS);

        return;
    }

	// case 3
	if (srcMS.getCurrVID() < tgtMS.getCurrVID()) {
        if (currID != srcMS.getCurrVID()) {
            currID = srcMS.getCurrVID();
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
                else cout << "ERROR: oUnUdPtr out of bounds" << endl;
            }
        }
        if (srcEdgesToMerge.size() > 0) updateMinSet(srcMS, srcEdgesToMerge, srcValsToMerge);
        minEdges.push(tgtMS);

        return;
    }
}

