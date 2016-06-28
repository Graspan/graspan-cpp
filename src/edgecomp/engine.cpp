#include <ctime>
#include "../../include/vertex.h"
#include "../../include/loadedvertexinterval.h"
#include "../../include/computationset.h"
#include "../../include/compute.h"
#include "../../include/randomgraphgen.h"


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
void computeOneIteration(std::vector<Vertex> vertices, ComputationSet compSets[], std::vector<LoadedVertexInterval> intervals, int indStart1, int indEnd1, int indStart2, int indEnd2)
{
    long newEdges;
    for (int i = 0; i < vertices.size(); i++)
    {   
        if (vertices.size() != 0)
        {
            newEdges = updateEdges(i, compSets, intervals);
        }
    }
}


/**
 * Get start and end indices of each partition
 *
 * @param vertices
 * @param compSets
 * @param intervals
 */
void computeEdges(std::vector<Vertex> vertices, ComputationSet compSets[], std::vector<LoadedVertexInterval> intervals)
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
	std::time_t startTime;
	std::time_t endTime;

	time(&startTime);

	std::vector<Vertex> vertices = randGraph();
	int pSize = vertices.size() / 2;

	ComputationSet *compSets = new ComputationSet[vertices.size()];
	
	for (int i = 0; i < vertices.size(); i++)
	{
		compSets[i].setNewEdges(vertices[i].getOutEdges());
		compSets[i].setNewVals(vertices[i].getOutEdgeValues());
		compSets[i].setoldUnewEdges(vertices[i].getOutEdges());
		compSets[i].setoldUnewVals(vertices[i].getOutEdgeValues());
	}

	std::vector<LoadedVertexInterval> lvi;
	lvi.reserve(2);

	lvi.push_back(LoadedVertexInterval{vertices[0].getVertexId(), vertices[pSize-1].getVertexId(), 0});
	lvi.push_back(LoadedVertexInterval{vertices[pSize].getVertexId(), vertices[vertices.size()-1].getVertexId(), 1});
	lvi[0].setIndexStart(0);
	lvi[0].setIndexEnd(pSize-1);
	lvi[1].setIndexStart(pSize);
	lvi[1].setIndexEnd(vertices.size()-1);

	computeEdges(vertices, compSets, lvi);

	delete[] compSets;

	time(&endTime);


	std::cout << std::endl << "Elapsed: " << endTime - startTime << std::endl;

	return 0;
}
