#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../utilities/globalDefinitions.hpp"

class Vertex
{
	int idx;

	int id;
	int numOutEdges;

	vector<int> outEdges;
	vector<char> outEdgeValues;
	

	public:
	// Constructors
	Vertex(int id, int outDegree);
	Vertex(int idx, int id, vector<int> outEdges, vector<char> outEdgeValues);

	// Getters
	int getVertexID();
	int getVertexIdx();
	int getNumOutEdges();
	vector<int> getOutEdges();
	vector<char> getOutEdgeValues();
	int getOutEdge(int ind);
	char getOutEdgeValue(int ind);

	// Setters
	void setNumOutEdges();
	void setOutEdges(vector<int> outEdges);
	void setOutEdgeValues(vector<char> outEdgeValues);

	string toString();
};


#endif
