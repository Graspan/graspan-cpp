#include <ctime>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../loader/loader.h"
#include "compute.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"

#define MAX_NEW_EDGES 3000000

long totNewEdges;
long newEdgesThisIter;
int iterNo;

bool newEdgesPart1;
bool newEdgesPart2;

// FUNCTION DEFS
void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2);

void initLVIs(LoadedVertexInterval intervals[], vector<Vertex> &part1, vector<Vertex> &part2);


/**
 * compute the new edges of each vertex simultaneously
 *
 * @param vertices
 * @param compsets
 * @param intervals
 */
void computeOneIteration(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Grammar &gram)
{
	#pragma omp parallel for
	for (int i = 0; i < setSize; i++)
	{
		long newEdges = 0;

		newEdges += updateEdges(i, compsets, intervals, gram);
		if (newEdges > 0 && (i >= intervals[0].getIndexStart() && i <= intervals[0].getIndexEnd()))
			intervals[0].setNewEdgeAdded(true);
		else if (newEdges > 0 && (i >= intervals[1].getIndexStart() && i <= intervals[1].getIndexEnd()))
			intervals[1].setNewEdgeAdded(true);

		#pragma omp atomic
		newEdgesThisIter += newEdges;
	}
}


/**
 * Get start and end indices of each partition
 *
 * @param vertices
 * @param compsets
 * @param intervals
 */
void computeEdges(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Grammar &gram)
{
	iterNo = 0;
	totNewEdges = 0;
	
	do {
		iterNo++;
		cout << "ITERATION: " << iterNo << endl;
		newEdgesThisIter = 0;
		computeOneIteration(compsets, setSize, intervals, gram);

		totNewEdges += newEdgesThisIter;

		cout << endl << endl;

		if (totNewEdges > MAX_NEW_EDGES) break;
	} while (newEdgesThisIter > 0);
}

/**
 * TEST SETUP
 * generates a random vector of vertices representing a graph, then sets up computation
 * sets and vertex intervals to have a test setup for computing new edges
 */
int main(int argc, char *argv[])
{
	Timer compTime;

	compTime.startTimer();

	// load partitions into memory
	Partition p1, p2;
	Loader::loadPartition(3, p1, true);
	Loader::loadPartition(4, p2, true);
	vector<Vertex> &part1 = p1.getData(), &part2 = p2.getData();

	cout << "PART 1:";
	for (int i = 0; i < part1.size(); i++)
		cout << part1[i].toString();

	cout << endl << endl << "PART 2:";
	for (int j = 0; j < part2.size(); j++)
		cout << part2[j].toString();

	// load grammar into memory
	Grammar gram;
	gram.loadGrammar("grammar");

	ComputationSet *compsets = new ComputationSet[part1.size() + part2.size()];
	int setSize = part1.size() + part2.size();

	initCompSets(compsets, part1, part2);
	
	// replace with primitive array
	LoadedVertexInterval intervals[2] = {LoadedVertexInterval{0}, LoadedVertexInterval{1}};
	initLVIs(intervals, part1, part2);

	for (int i = 0; i < 2; i++)
	{
		LoadedVertexInterval lvi = intervals[i];
		cout << lvi.toString() << endl;
	}

	computeEdges(compsets, setSize, intervals, gram);

//	saveNewEdges(compsets, intervals, part1, part2);

	delete[] compsets;

	compTime.endTimer();


	cout << "TOTAL TIME: " << compTime.toString() << endl;

	return 0;
}

void saveNewEdges(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	for (int i = 0; i < part1.size(); i++)
	{
		part1[i].setOutEdges(compsets[i].getoldUnewEdges());
		part1[i].setOutEdgeValues(compsets[i].getoldUnewVals());
	}

	int offset = part1.size();
	for (int j = 0; j < part2.size(); j++)
	{
		part2[j].setOutEdges(compsets[j+offset].getoldUnewEdges());
		part2[j].setOutEdgeValues(compsets[j].getoldUnewVals());
	}
}

void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	for (int i = 0; i < part1.size(); i++)
	{
		compsets[i].setNewEdges(part1[i].getOutEdges());
		compsets[i].setNewVals(part1[i].getOutEdgeValues());
		compsets[i].setoldUnewEdges(part1[i].getOutEdges());
		compsets[i].setoldUnewVals(part1[i].getOutEdgeValues());
	}

	int offset = part1.size();
	for (int j = part1.size(); j < part1.size() + part2.size(); j++)
	{
		compsets[j].setNewEdges(part2[j - offset].getOutEdges());
		compsets[j].setNewVals(part2[j - offset].getOutEdgeValues());
		compsets[j].setoldUnewEdges(part2[j - offset].getOutEdges());
		compsets[j].setoldUnewVals(part2[j - offset].getOutEdgeValues());
	}
}

void initLVIs(LoadedVertexInterval intervals[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	intervals[0].setFirstVertex(part1[0].getVertexID());
	intervals[0].setLastVertex(part1[part1.size() - 1].getVertexID());
	intervals[0].setIndexStart(0);
	intervals[0].setIndexEnd(part1.size()-1);

	intervals[1].setFirstVertex(part2[0].getVertexID());
	intervals[1].setLastVertex(part2[part2.size() - 1].getVertexID());
	intervals[1].setIndexStart(part1.size());
	intervals[1].setIndexEnd(part1.size() + part2.size()-1);
}
