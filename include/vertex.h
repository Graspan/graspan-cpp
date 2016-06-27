#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>


class Vertex
{
	int idx;

	int id;
	int numOutEdges;

	std::vector<int> outEdges;
	std::vector<char> outEdgeValues;
	

	public:
	// Constructors
	Vertex(int id, int outDegree);
	Vertex(int idx, int id, std::vector<int> outEdges, std::vector<char> outEdgeValues);

	// Getters
	int getVertexId();
	int getVertexIdx();
	int getNumOutEdges();
	std::vector<int> getOutEdges();
	std::vector<char> getOutEdgeValues();
	int getOutEdge(int ind);
	char getOutEdgeValue(int ind);

	// Setters
	void setNumOutEdges();
	void setOutEdges(std::vector<int> outEdges);
	void setOutEdgeValues(std::vector<char> outEdgeValues);

	std::string toString();
};


#endif
