#include "../../include/compute.h"
#include "../../include/merge.h"
#include "../../include/timer.h"


// FUNCTION DEFINITIONS
void getRowIndsToMerge(ComputationSet compSets[], std::vector<LoadedVertexInterval> &intervals,
		std::vector<int> &edges, std::vector<char> &vals, bool edgesEmpty,
		std::unordered_set<IDValuePair, Hash> &newIDsToMerge, char flag);

void genEdgesToMergeForSRule(std::vector<int> &newEdges, std::vector<char> &newVals,
		std::vector< std::vector<int> > &edgeVecsToMerge,
		std::vector< std::vector<char> > &valVecsToMerge, int &rowMergeID);

void genEdgesToMergeForDRule(ComputationSet compSets[], std::unordered_set<IDValuePair, Hash> &IDsToMerge,
		std::vector< std::vector<int> > &edgeVecsToMerge, std::vector< std::vector<char> > &valVecsToMerge,
		int &rowMergeID, char flag);

/**
 * given an index into the compSets, 
 */
long updateEdges(int i, ComputationSet compSets[], std::vector<LoadedVertexInterval> &intervals)
{
	ComputationSet compSet = compSets[i];

	// get the list of dest vertices of the current source vertex
	std::vector<int> oldEdges = compSet.getOldEdges();
	std::vector<char> oldVals = compSet.getOldVals();

	std::vector<int> newEdges = compSet.getNewEdges();
	std::vector<char> newVals = compSet.getNewVals();

	bool oldEdgesEmpty = (oldEdges.empty()) ? true : false;
	bool newEdgesEmpty = (newEdges.empty()) ? true : false;

	if (oldEdgesEmpty && newEdgesEmpty) return 0;


	// get the indices of the rows to merge with their grammar
	std::unordered_set<IDValuePair, Hash> newRowIndsToMerge;
	std::unordered_set<IDValuePair, Hash> oldUnewRowIndsToMerge;

	getRowIndsToMerge(compSets, intervals, oldEdges, oldVals, oldEdgesEmpty, newRowIndsToMerge, 'o');
	getRowIndsToMerge(compSets, intervals, newEdges, newVals, newEdgesEmpty, oldUnewRowIndsToMerge, 'n');
	
	int numRowsToMerge = 2 + oldUnewRowIndsToMerge.size() + newRowIndsToMerge.size();

	std::vector< std::vector<int> > edgeVecsToMerge(numRowsToMerge);
	std::vector< std::vector<char> > valVecsToMerge(numRowsToMerge);

	int rowToMergeID = 0;
	edgeVecsToMerge[rowToMergeID] = compSet.getoldUnewEdges();
	valVecsToMerge[rowToMergeID++] = compSet.getoldUnewVals();
	

	genEdgesToMergeForSRule(newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowToMergeID);

	genEdgesToMergeForDRule(compSets, newRowIndsToMerge, edgeVecsToMerge, valVecsToMerge, rowToMergeID, 'o');
	genEdgesToMergeForDRule(compSets, oldUnewRowIndsToMerge, edgeVecsToMerge, valVecsToMerge, rowToMergeID, 'n');

	
	vecMerge(edgeVecsToMerge, valVecsToMerge, 0);

	return 0;
}

/**
 * checks if any of the vertices pointed to by the source are in the current partition and if so
 * gets their index into the list of ComputationSets and adds it to newIDsToMerge
 *
 * @param compSets			@param edgesEmpty
 * @param intervals			@param newIDsToMerge
 * @param edges				@param flag
 * @param vals
 */
void getRowIndsToMerge(ComputationSet compSets[], std::vector<LoadedVertexInterval> &intervals,
		std::vector<int> &edges, std::vector<char> &vals, bool edgesEmpty,
		std::unordered_set<IDValuePair, Hash> &newIDsToMerge, char flag)
{
	int targetRowIndex = -1;

	int newTgt = 0;
	char val = 0;

	if (!edgesEmpty)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			newTgt = edges[i];
			val = vals[i];

			for (int j = 0; j < intervals.size(); j++)
			{
				targetRowIndex = -1;
				LoadedVertexInterval interval = intervals[j];
				if (newTgt >= interval.getFirstVertex() && newTgt <= interval.getLastVertex())
				{
					targetRowIndex = newTgt - interval.getFirstVertex() + interval.getIndexStart();
					break;
				}
			}
			if (targetRowIndex == -1) continue;

			if ((flag == 'o' && compSets[targetRowIndex].getNewEdges().size() > 0) ||
				(flag == 'n' && compSets[targetRowIndex].getoldUnewEdges().size() > 0))
					newIDsToMerge.insert(IDValuePair{targetRowIndex, val});
		}
	}
}

/**
 * For each edge in the outgoing edges list, check if the grammar for a "S Rules" (single
 * char) rules applies. If so, add it to the new edge list to be merged
 *
 * @param newEdges					@param valVecsToMerge
 * @param newVals					@param rowMergeID
 * @param edgeVecsToMerge
 */
void genEdgesToMergeForSRule(std::vector<int> &newEdges, std::vector<char> &newVals,
		std::vector< std::vector<int> > &edgeVecsToMerge,
		std::vector< std::vector<char> > &valVecsToMerge, int &rowMergeID)
{
//	std::vector<int> newEdgesVec;
//	std::vector<char> newValsVec;
	char newEdgeVal;
	for (int i = 0; i < newEdges.size(); i++)
	{
		newEdgeVal = GrammarChecker::checkL1Rules(newVals[i]);
		if (newEdgeVal != (char)-1) {
			edgeVecsToMerge[rowMergeID].push_back(newEdges[i]);
			valVecsToMerge[rowMergeID].push_back(newEdgeVal);
//			newEdgesVec.push_back(newEdges[i]);
//			newValsVec.push_back(newVals[i]);
		}
	}
	rowMergeID++;

//	edgeVecsToMerge[rowMergeID] = newEdgesVec;
//	valVecsToMerge[rowMergeID++] = newValsVec;	
}


/**
 * For each destination vertex, check its list of outgoing edges to see if any match with the 
 * grammar for "D Rules" (double chars) applies. If so, add it to the new edges list to be merged
 *
 * @param compSets				@param valVecsToMerge
 * @param IDsToMerge			@param rowMergeID
 * @param edgeVecsToMerge		@param flag
 */
void genEdgesToMergeForDRule(ComputationSet compSets[], std::unordered_set<IDValuePair, Hash> &IDsToMerge,
		std::vector< std::vector<int> > &edgeVecsToMerge, std::vector< std::vector<char> > &valVecsToMerge,
		int &rowMergeID, char flag)
{
	for (std::unordered_set<IDValuePair, Hash>::iterator iter = IDsToMerge.begin(); iter != IDsToMerge.end(); iter++)
	{
		// the outgoing edges and values (of each outgoing edge from the source vertex)
		std::vector<int> edges = (flag == 'o') ? compSets[iter->id].getNewEdges() : compSets[iter->id].getoldUnewEdges();
		std::vector<char> vals = (flag == 'o') ? compSets[iter->id].getNewVals() : compSets[iter->id].getoldUnewVals();

//		std::vector<int> newEdgesVec;
//		std::vector<char> newValsVec;
		char newEdgeVal;
		for (int i = 0; i < edges.size(); i++)
		{
			newEdgeVal = GrammarChecker::checkL2Rules(iter->val, vals[i]);
			if (newEdgeVal != (char)-1) {
				edgeVecsToMerge[rowMergeID].push_back(edges[i]);
				valVecsToMerge[rowMergeID].push_back(newEdgeVal);
//				newEdgesVec.push_back(edges[i]);
//				newValsVec.push_back(vals[i]);
			}
		}

		rowMergeID++;
//		edgeVecsToMerge[rowMergeID] = newEdgesVec;
//		valVecsToMerge[rowMergeID++] = newValsVec;
	}
}
