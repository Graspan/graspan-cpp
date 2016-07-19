#include <ctime>

#include <fstream>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../loader/loader.h"
#include "compute.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"

long totNewEdges;
long newEdgesThisIter;
int iterNo;

bool newEdgesPart1;
bool newEdgesPart2;

// FUNCTION DEFS
void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2);

void initLVIs(vector<LoadedVertexInterval> intervals, vector<Vertex> &data1, vector<Vertex> &data2);


/**
 * compute the new edges of each vertex simultaneously
 *
 * @param vertices
 * @param compSets
 * @param intervals
 */
void computeOneIteration(vector<Vertex> &vertices, ComputationSet compSets[],
		vector<LoadedVertexInterval> &intervals, Grammar &gram)
{
//	if (vertices[0].getNumOutEdges() != 0) {
//		cout << "Updating vertex " << vertices[2].getVertexID() << "..." << endl;
//		updateEdges(2, compSets, intervals, gram);
//	}
//	else cout << "Vertex " << vertices[0].getVertexID() << " has no edges" << endl;

	#pragma omp parallel for
	for (int i = 0; i < vertices.size(); i++)
	{
		long newEdges = 0;
		if (vertices[i].getNumOutEdges() != 0) {
			cout << "Updating vertex " << vertices[i].getVertexID() << "..." << endl;
			
			newEdges += updateEdges(i, compSets, intervals, gram);

			#pragma omp atomic
			newEdgesThisIter += newEdges;
		}
		else { cout << "Vertex " << vertices[i].getVertexID() << " has no edges" << endl << std::endl; }
	}
}


/**
 * Get start and end indices of each partition
 *
 * @param vertices
 * @param compSets
 * @param intervals
 */
void computeEdges(vector<Vertex> &vertices, ComputationSet compSets[], vector<LoadedVertexInterval> &intervals, Grammar &gram)
{
	iterNo = 0;
	totNewEdges = 0;
	
	do {
		iterNo++;
		cout << "ITERATION: " << iterNo << endl;
		newEdgesThisIter = 0;
		computeOneIteration(vertices, compSets, intervals, gram);

		totNewEdges += newEdgesThisIter;

		cout << endl << endl;
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
	vector<Vertex> &data1 = p1.getData(), &data2 = p2.getData();

//	vector<Vertex> vertices;
//	vertices.reserve(data1.size() + data2.size());
//
//	vertices.insert(vertices.end(), data1.begin(), data1.end());
//	vertices.insert(vertices.end(), data2.begin(), data2.end());
//
//	for (int j = 0; j < vertices.size(); j++)
//		cout << vertices[j].toString() << endl;

	// load grammar into memory
	Grammar g;
	g.loadGrammar("grammar");

	ComputationSet *compSets = new ComputationSet[vertices.size()];

	initCompSets(compSets, data1, data2);
	
	// replace with primitive array
	vector<LoadedVertexInterval> lvi;
	lvi.reserve(2);
	initLVIs(lvi, data1, data2);

	computeEdges(compSets, lvi, g);

	delete[] compSets;

	compTime.endTimer();


	cout << "TOTAL TIME: " << compTime.toString() << endl;

	return 0;
}

void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	for (int i = 0; i < data1.size(); i++)
	{
		compSets[i].setNewEdges(vertices[i].getOutEdges());
		compSets[i].setNewVals(vertices[i].getOutEdgeValues());
		compSets[i].setoldUnewEdges(vertices[i].getOutEdges());
		compSets[i].setoldUnewVals(vertices[i].getOutEdgeValues());
	}

	for (int j = data1.size(); j < data1.size() + data2.size(); j++)
	{
		compSets[j].setNewEdges(vertices[j].getOutEdges());
		compSets[j].setNewVals(vertices[j].getOutEdgeValues());
		compSets[j].setoldUnewEdges(vertices[j].getOutEdges());
		compSets[j].setoldUnewVals(vertices[j].getOutEdgeValues());
	}
}

void initLVIs(vector<LoadedVertexInterval> intervals, vector<Vertex> &data1, vector<Vertex> &data2)
{
	lvi.push_back(LoadedVertexInterval{data1[0].getVertexID(), data1[data1.size() - 1].getVertexID(), 0});
	lvi[0].setIndexStart(0);
	lvi[0].setIndexEnd(data1.size()-1);

	lvi.push_back(LoadedVertexInterval{data2[0].getVertexID(), data2[data2.size() - 1].getVertexID(), 1});
	lvi[1].setIndexStart(data1.size());
	lvi[1].setIndexEnd(data1.size() + data2.size()-1);
}
