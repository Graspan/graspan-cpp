#include "compute.h"
#include "../../test/timer.h"


// FUNCTION DEFINITIONS
void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Grammar &gram);

void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		int &rowMergeID, Grammar &gram);

void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsTomerge, int &rowMergeID, Grammar &gram, char flag);

void checkEdges(int dstInd, char dstVal, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int &rowMergeID,
		Grammar &gram, char flag);

void print_edges(vector<vector<int>> &edgeVecsToMerge, vector<vector<char>> &valVecsToMerge)
{
	for (int i = 0; i < edgeVecsToMerge.size(); i++)
	{
		if (edgeVecsToMerge[i].size() == 0) cout << "VEC" << i << ": empty..." << endl;
		else {
			cout << "VEC" << i << ": ";
			for (int j = 0; j < edgeVecsToMerge[i].size(); j++)
				cout << "(" << edgeVecsToMerge[i][j] << ", " << (short)valVecsToMerge[i][j] << ")  ";

			cout << endl;
		}
	}
	cout << endl;
}


/**
 * given an index into the compsets, find all valid edges and merge them into a new list
 *
 * @param vertInd			-index of source vertex in compsets[]
 * @param compsets[]		-ComputationSet list for all in-memory vertices
 * @param intervals			-list (size=2) with information about the partitions
 * @param gram				-Grammar object for checking grammar
 */
long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Grammar &gram)
{
	ComputationSet *compSet = &compsets[vertInd];

	bool oldEdgesEmpty = (compSet->getOldEdges().empty()) ? true : false;
	bool newEdgesEmpty = (compSet->getNewEdges().empty()) ? true : false;

	if (oldEdgesEmpty && newEdgesEmpty) return 0;


	// TODO: use DDM to estimate num of rows needed
	int numRowsToMerge = 2 + compSet->getoldUnewEdges().size();
	vector< vector<int> > edgeVecsToMerge(numRowsToMerge);;
	vector< vector<char> > valVecsToMerge(numRowsToMerge);

	int rowMergeID = 0;
	edgeVecsToMerge[rowMergeID] = compSet->getoldUnewEdges();
	valVecsToMerge[rowMergeID++] = compSet->getoldUnewVals();

	getEdgesToMerge(compSet, compsets, intervals, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram);

//	print_edges(edgeVecsToMerge, valVecsToMerge);

	// get the indices of the rows to merge with their grammar
//	vector< pair<int, char> > prevRowInds;
//	vector< pair<int, char> > newRowInds;
//
//	// TODO: combine getRowInds with genEdgesToMerge
//	getRowInds(compsets, intervals, oldEdges, oldVals, oldEdgesEmpty, newRowIndsToMerge, 'o');
//	getRowInds(compsets, intervals, newEdges, newVals, newEdgesEmpty, oldUnewRowIndsToMerge, 'n');
//	
//	int numRowsToMerge = 2 + oldUnewRowIndsToMerge.size() + newRowIndsToMerge.size();
//
//	vector< vector<int> > edgeVecsToMerge(numRowsToMerge);
//	vector< vector<char> > valVecsToMerge(numRowsToMerge);
//
//	int rowToMergeID = 0;
//	edgeVecsToMerge[rowToMergeID] = compSet->getoldUnewEdges();
//	valVecsToMerge[rowToMergeID++] = compSet->getoldUnewVals();
//	
//
//	genEdgesToMergeForSRule(newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowToMergeID, gram);
//
//	genEdgesToMergeForDRule(compsets, newRowIndsToMerge, edgeVecsToMerge, valVecsToMerge, rowToMergeID, gram, 'o');
//	genEdgesToMergeForDRule(compsets, oldUnewRowIndsToMerge, edgeVecsToMerge, valVecsToMerge, rowToMergeID, gram, 'n');

	EdgeMerger em;

	em.mergeVectors(edgeVecsToMerge, valVecsToMerge, 0);

	#pragma omp barrier
	compSet->setOldEdges(compSet->getoldUnewEdges());
	compSet->setOldVals(compSet->getoldUnewVals());
	compSet->setoldUnewEdges(em.getoUnUdEdges());
	compSet->setoldUnewVals(em.getoUnUdVals());
	compSet->setNewEdges(em.getDeltaEdges());
	compSet->setNewVals(em.getDeltaVals());

	return em.getNumNewEdges();
}

/**
 * @param CompSet			-ComputationSet of source vertex
 * @param compsets[] 		-ComputationSet list of in-mem vertices
 * @param intervals[] 		-information about partition intervals
 * @param edgeVecsToMerge	-2D vector of sorted edges to merge
 * @param valVecsToMerge	-2D vector of vals associated with edges
 * @param rowMergeID		-current row to add edges to
 * @param gram				-grammar checker
 */
void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Grammar &gram)
{
	vector<int> &oldEdges = compSet->getOldEdges();
	vector<char> &oldVals = compSet->getOldVals();

	vector<int> &newEdges = compSet->getNewEdges();
	vector<char> &newVals = compSet->getNewVals();

	genS_RuleEdges(newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram);

	genD_RuleEdges(compsets, intervals, oldEdges, oldVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram, 'o');
	genD_RuleEdges(compsets, intervals, newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram, 'n');
}

/**
 * checks if any of the vertices pointed to by the source are in the current partition and if so
 * gets their index into the list of ComputationSets and adds it to newIDsToMerge
 *
 * @param compsets			@param edgesEmpty
 * @param intervals			@param newIDsToMerge
 * @param edges				@param flag
 * @param vals
 */
void getRowIndsToMerge(ComputationSet compsets[], LoadedVertexInterval intervals[],
		vector<int> &edges, vector<char> &vals, bool edgesEmpty, vector< pair<int, char> > &newRowInds,
		char flag)
{
	int targetRowIndex = -1;

	int newTgt = 0;
	char val = 0;

	if (!edgesEmpty) {
		for (int i = 0; i < edges.size(); i++) {
			newTgt = edges[i];
			val = vals[i];

			for (int j = 0; j < 2; j++) {
				targetRowIndex = -1;
				LoadedVertexInterval *interval = &intervals[j];
				if (newTgt >= interval->getFirstVertex() && newTgt <= interval->getLastVertex()) {
					targetRowIndex = newTgt - interval->getFirstVertex() + interval->getIndexStart();
					break;
				}
			}
			if (targetRowIndex == -1) continue;

			if ((flag == 'o' && compsets[targetRowIndex].getNewEdges().size() > 0) ||
				(flag == 'n' && compsets[targetRowIndex].getoldUnewEdges().size() > 0))
					newRowInds.push_back({targetRowIndex, val});
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
void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		int &rowMergeID, Grammar &gram)
{
//	vector<int> newEdgesVec;
//	vector<char> newValsVec;
	char newEdgeVal;
	for (int i = 0; i < newEdges.size(); i++) {
		newEdgeVal = gram.checkRules(newVals[i], 0);
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

void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Grammar &gram, char flag)
{
	int dstInd;
	for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (edges[i] >= intervals[j].getFirstVertex() && edges[i] <= intervals[j].getLastVertex()) {
				dstInd = intervals[j].getIndexStart() + (edges[i] - intervals[j].getFirstVertex());
				if (flag == 'o' && compsets[dstInd].getNewEdges().size() > 0)
					checkEdges(dstInd, vals[i], compsets, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram, flag);
				else if (flag == 'n' && compsets[dstInd].getoldUnewEdges().size() > 0)
					checkEdges(dstInd, vals[i], compsets, edgeVecsToMerge, valVecsToMerge, rowMergeID, gram, flag);
			}
		}
	}
}

void checkEdges(int dstInd, char dstVal, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int &rowMergeID,
		Grammar &gram, char flag)
{
	vector<int> &edges = (flag == 'o') ? compsets[dstInd].getNewEdges() : compsets[dstInd].getoldUnewEdges();
	vector<char> &vals = (flag == 'o') ? compsets[dstInd].getNewVals() : compsets[dstInd].getoldUnewVals();

	char newVal;
	for (int i = 0; i < edges.size(); i++)
	{
		newVal = gram.checkRules(dstVal, vals[i]);
		if (newVal != (char)-1) {
			edgeVecsToMerge[rowMergeID].push_back(edges[i]);
			valVecsToMerge[rowMergeID].push_back(newVal);
		}
	}
	rowMergeID++;
}


/**
 * For each destination vertex, check its list of outgoing edges to see if any match with the 
 * grammar for "D Rules" (double chars) applies. If so, add it to the new edges list to be merged
 *
 * @param compsets				@param valVecsToMerge
 * @param IDsToMerge			@param rowMergeID
 * @param edgeVecsToMerge		@param flag
 */
void genEdgesToMergeForDRule(ComputationSet compsets[], std::unordered_set<IDValuePair, Hash> &IDsToMerge,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		int &rowMergeID, Grammar &gram, char flag)
{
	for (std::unordered_set<IDValuePair, Hash>::iterator iter = IDsToMerge.begin(); iter != IDsToMerge.end(); iter++) {
		// the outgoing edges and values (of each outgoing edge from the source vertex)
		vector<int> edges = (flag == 'o') ? compsets[iter->id].getNewEdges() : compsets[iter->id].getoldUnewEdges();
		vector<char> vals = (flag == 'o') ? compsets[iter->id].getNewVals() : compsets[iter->id].getoldUnewVals();

//		vector<int> newEdgesVec;
//		vector<char> newValsVec;
		char newEdgeVal;
		for (int i = 0; i < edges.size(); i++) {
			newEdgeVal = gram.checkRules(iter->val, vals[i]);
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
