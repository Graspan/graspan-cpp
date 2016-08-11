#include "compute.h"
#include "../../test/timer.h"


// FUNCTION DEFINITIONS
void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Context &context);

void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		int &rowMergeID, Context &context);

void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsTomerge, int &rowMergeID, Context &context, char flag);

void checkEdges(int dstInd, char dstVal, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int &rowMergeID,
		Context &context, char flag);

// PRINT EDGES FOR DEBUGGING
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
 * @param context				-Context object for checking grammar
 */
long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Context &context, short numRules)
{
	ComputationSet *compSet = &compsets[vertInd];

	bool oldEdgesEmpty = (compSet->getOldEdges().empty()) ? true : false;
	bool newEdgesEmpty = (compSet->getNewEdges().empty()) ? true : false;

	if (oldEdgesEmpty && newEdgesEmpty) return 0;


	// TODO: use DDM to estimate num of rows needed
	vector< vector<double> > &ddm = context.ddm.getDdmMap();
	int numRowsToMerge = 2 + compSet->getoldUnewEdges().size();
	vector< vector<int> > edgeVecsToMerge(numRowsToMerge);;
	vector< vector<char> > valVecsToMerge(numRowsToMerge);

	int rowMergeID = 0;
	edgeVecsToMerge[rowMergeID] = compSet->getoldUnewEdges();
	valVecsToMerge[rowMergeID++] = compSet->getoldUnewVals();

	getEdgesToMerge(compSet, compsets, intervals, edgeVecsToMerge, valVecsToMerge, rowMergeID, context);

	EdgeMerger em;

	em.mergeVectors(edgeVecsToMerge, valVecsToMerge, 0, numRules);

	compSet->setDeltaEdges(em.getDeltaEdges());
	compSet->setDeltaVals(em.getDeltaVals());
	compSet->setoUnUdEdges(em.getoUnUdEdges());
	compSet->setoUnUdVals(em.getoUnUdVals());
	
//	compSet->setOldEdges(compSet->getoldUnewEdges());
//	compSet->setOldVals(compSet->getoldUnewVals());
//	compSet->setoldUnewEdges(em.getoUnUdEdges());
//	compSet->setoldUnewVals(em.getoUnUdVals());
//	compSet->setNewEdges(em.getDeltaEdges());
//	compSet->setNewVals(em.getDeltaVals());

	return em.getNumNewEdges();
}

/**
 * @param CompSet			-ComputationSet of source vertex
 * @param compsets[] 		-ComputationSet list of in-mem vertices
 * @param intervals[] 		-information about partition intervals
 * @param edgeVecsToMerge	-2D vector of sorted edges to merge
 * @param valVecsToMerge	-2D vector of vals associated with edges
 * @param rowMergeID		-current row to add edges to
 * @param context				-grammar checker
 */
void getEdgesToMerge(ComputationSet *compSet, ComputationSet compsets[],
		LoadedVertexInterval intervals[], vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Context &context)
{
	vector<int> &oldEdges = compSet->getOldEdges();
	vector<char> &oldVals = compSet->getOldVals();

	vector<int> &newEdges = compSet->getNewEdges();
	vector<char> &newVals = compSet->getNewVals();

	genS_RuleEdges(newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, context);

	genD_RuleEdges(compsets, intervals, oldEdges, oldVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, context, 'o');
	genD_RuleEdges(compsets, intervals, newEdges, newVals, edgeVecsToMerge, valVecsToMerge, rowMergeID, context, 'n');
}

/**
 * For each edge in the outgoing edges list, check if the contextmar for a "S Rules" (single
 * char) rules applies. If so, add it to the new edge list to be merged
 *
 * @param newEdges				-vector of only most recently added edges
 * @param newVals				-vector of values corresponding to new edges
 * @param edgeVecsToMerge		-vector of vectors of edges to merge with source
 * @param valVecsToMerge		-vector of vecotrs of vals to merge with source
 * @param rowMergeID			-current row of vector to add
 * @param context					-grammar checker
 */
void genS_RuleEdges(vector<int> &newEdges, vector<char> &newVals,
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge,
		int &rowMergeID, Context &context)
{
	char newEdgeVal;
	for (int i = 0; i < newEdges.size(); i++) {
		newEdgeVal = context.grammar.checkRules(newVals[i], 0);
		if (newEdgeVal != (char)-1) {
			edgeVecsToMerge[rowMergeID].push_back(newEdges[i]);
			valVecsToMerge[rowMergeID].push_back(newEdgeVal);
		}
	}
	rowMergeID++;
}

/**
 * For each outgoing edge of the source vertex that points to a vertex currently loaded into memory
 * check the edges of that vertex against the contextmar
 */
void genD_RuleEdges(ComputationSet compsets[], LoadedVertexInterval intervals[], vector<int> &edges,
		vector<char> &vals, vector< vector<int> > &edgeVecsToMerge,
		vector< vector<char> > &valVecsToMerge, int &rowMergeID, Context &context, char flag)
{
	int dstInd;
	for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (edges[i] >= intervals[j].getFirstVertex() && edges[i] <= intervals[j].getLastVertex()) {
				dstInd = intervals[j].getIndexStart() + (edges[i] - intervals[j].getFirstVertex());
				if (flag == 'o' && compsets[dstInd].getNewEdges().size() > 0)
					checkEdges(dstInd, vals[i], compsets, edgeVecsToMerge, valVecsToMerge, rowMergeID, context, flag);
				else if (flag == 'n' && compsets[dstInd].getoldUnewEdges().size() > 0)
					checkEdges(dstInd, vals[i], compsets, edgeVecsToMerge, valVecsToMerge, rowMergeID, context, flag);
			}
		}
	}
}

/**
 * given an index into the ComputationSet list, and the edge value of that vertex, check if any of
 * the outgoing edges fit the contextmar and if so add them to the vector to be merged with the source
 */
void checkEdges(int dstInd, char dstVal, ComputationSet compsets[],
		vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int &rowMergeID,
		Context &context, char flag)
{
	vector<int> &edges = (flag == 'o') ? compsets[dstInd].getNewEdges() : compsets[dstInd].getoldUnewEdges();
	vector<char> &vals = (flag == 'o') ? compsets[dstInd].getNewVals() : compsets[dstInd].getoldUnewVals();

	char newVal;
	for (int i = 0; i < edges.size(); i++)
	{
		newVal = context.grammar.checkRules(dstVal, vals[i]);
		if (newVal != (char)-1) {
			edgeVecsToMerge[rowMergeID].push_back(edges[i]);
			valVecsToMerge[rowMergeID].push_back(newVal);
		}
	}
	rowMergeID++;
}
