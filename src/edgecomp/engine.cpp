#include <ctime>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../edgecomp/grammarchecker.h"
#include "../edgecomp/compute.h"
#include "../../test/randomgraphgen.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"


void loadGrammar();


// TODO: ADD TIMERS TO TEST PERFORMANCE

/**
 * TODO: Make multithreaded
 * compute the new edges of each vertex simultaneously
 *
 * @param vertices		@param indEnd1
 * @param compSets		@param indStart2
 * @param intervals		@param indEnd2
 * @param indStart1
 */
void computeOneIteration(vector<Vertex> &vertices, ComputationSet compSets[],
		vector<LoadedVertexInterval> &intervals, int indStart1, int indEnd1,
		int indStart2, int indEnd2)
{
//	if (vertices[0].getNumOutEdges() != 0) {
//		cout << "Updating vertex " << vertices[0].getVertexID() << "..." << endl;
//		updateEdges(0, compSets, intervals);
//	}
//	else cout << "Vertex " << vertices[0].getVertexID() << " has no edges" << endl;

	long newEdges;
	for (int i = 0; i < vertices.size(); i++) {   
		if (vertices[i].getNumOutEdges() != 0) {
			cout << "Updating vertex " << vertices[i].getVertexID() << "..." << endl;
			newEdges = updateEdges(i, compSets, intervals);
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
void computeEdges(vector<Vertex> &vertices, ComputationSet compSets[], std::vector<LoadedVertexInterval> &intervals)
{
	if (vertices.size() == 0) return;

	int indStart1 = intervals[0].getIndexStart();
	int indEnd1 = intervals[0].getIndexEnd();
	int indStart2 = intervals[1].getIndexStart();
	int indEnd2 = intervals[1].getIndexEnd();

	computeOneIteration(vertices, compSets, intervals, indStart1, indEnd1, indStart2, indEnd2);
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

	cout << "==== GRAPH ====" << endl;
	vector<Vertex> vertices = randGraph();
	int pSize = vertices.size() / 2;

	// temp function for testing
	cout << "==== GRAMMAR ====" << endl;
	loadGrammar();

	ComputationSet *compSets = new ComputationSet[vertices.size()];
	
	for (int i = 0; i < vertices.size(); i++)
	{
		compSets[i].setNewEdges(vertices[i].getOutEdges());
		compSets[i].setNewVals(vertices[i].getOutEdgeValues());
		compSets[i].setoldUnewEdges(vertices[i].getOutEdges());
		compSets[i].setoldUnewVals(vertices[i].getOutEdgeValues());
	}

	vector<LoadedVertexInterval> lvi;
	lvi.reserve(2);

	lvi.push_back(LoadedVertexInterval{vertices[0].getVertexID(), vertices[pSize-1].getVertexID(), 0});
	lvi.push_back(LoadedVertexInterval{vertices[pSize].getVertexID(), vertices[vertices.size()-1].getVertexID(), 1});
	lvi[0].setIndexStart(0);
	lvi[0].setIndexEnd(pSize-1);
	lvi[1].setIndexStart(pSize);
	lvi[1].setIndexEnd(vertices.size()-1);

	computeEdges(vertices, compSets, lvi);

	delete[] compSets;

	compTime.endTimer();


	cout << "TOTAL TIME: " << compTime.toString() << endl;

	return 0;
}


string make_chars(short s)
{
	string str = "";
	char a = s >> 8;
	char b = (char)s;

	str += a; str += b;
	return str;
}

// delete later
void loadGrammar()
{
	GrammarChecker::addSRule('a', 'd');
	GrammarChecker::addSRule('c', 'a');

	GrammarChecker::addDRule('c', 'a', 'd');
	GrammarChecker::addDRule('d', 'b', 'c');
	GrammarChecker::addDRule('c', 'b', 'a');

	cout << "GRAM_RULES: ";
	for (std::unordered_map<short, char>::iterator iter = GrammarChecker::gramRules.begin(); iter != GrammarChecker::gramRules.end(); iter++)
	{
		cout << "([" << make_chars(iter->first) << "] -> " << iter->second << ")  ";
	}
	cout << endl << std::endl;
}
