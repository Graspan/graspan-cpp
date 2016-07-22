#ifndef VERTEX_H
#define VERTEX_H

#include <sstream>
#include "../utilities/globalDefinitions.hpp"

//TODO: clean this up
class Vertex
{
	int idx;

	vertexid_t id;
	int numOutEdges;

	vector<vertexid_t> outEdges;
	vector<label_t> outEdgeValues;
	

	public:
	// Constructors
	Vertex() {};
	Vertex(int id, int outDegree);
	Vertex(int idx, int id, vector<int> outEdges, vector<char> outEdgeValues);

  //ALL small methods should be inlined!!!
	// Getters
	int getVertexID();
	int getVertexIdx();
	int getNumOutEdges();
	vector<int> &getOutEdges();
	vector<char> &getOutEdgeValues();
	int getOutEdge(int ind);
	char getOutEdgeValue(int ind);

	// Setters
	void setNumOutEdges(int numEdges);
	void setOutEdges(vector<int> &outEdges);
	void setOutEdgeValues(vector<char> &outEdgeValues);

	string toString();
};


#endif
