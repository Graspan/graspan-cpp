#include "vertex.h"

// Constructors
Vertex::Vertex(int idx, int id, vector<int> outEdges, vector<char> outEdgeValues)
{
	this->idx = idx;
	this->id = id;
	this->numOutEdges = 0;
	this->outEdges = outEdges;
	this->outEdgeValues = outEdgeValues;

	numOutEdges = outEdges.size();
}


/**
 * Description: display a vertex as its id and the destination vertices it points to
 * with their grammar
 *
 * @return string output
 */
string Vertex::toString()
{
	std::stringstream output;

	output << endl << id << " ->  ";
	for (int i = 0; i < numOutEdges; i++)
		output << "(" << outEdges[i] << ", " << (short)(outEdgeValues[i]) << ")  ";


	return output.str();
}
