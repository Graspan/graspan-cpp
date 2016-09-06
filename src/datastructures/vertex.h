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
	inline int getVertexID() { return id; }
	inline int getVertexIdx() { return idx; }
	inline int getNumOutEdges() { return numOutEdges; }
	inline vector<int> &getOutEdges() { return outEdges; }
	inline vector<char> &getOutEdgeValues() { return outEdgeValues; }
	inline int getOutEdge(int ind) { return outEdges[ind]; }
	inline char getOutEdgeValue(int ind) { return outEdgeValues[ind]; }

	// Setters
	inline void setNumOutEdges(int numEdges) { this->numOutEdges = numEdges; }
	inline void setOutEdges(vector<int> &outEdges) { this->outEdges = outEdges; }
	inline void setOutEdgeValues(vector<char> &outEdgeValues) { this->outEdgeValues = outEdgeValues; }

	inline void clearVector() { 
		outEdges.erase(outEdges.begin(), outEdges.begin()+ numOutEdges);
		outEdgeValues.erase(outEdgeValues.begin(), outEdgeValues.begin() + numOutEdges);
		
		vector<vertexid_t>().swap(outEdges);
		vector<label_t>().swap(outEdgeValues);
		numOutEdges = 0;
	};
	
	string toString();
};


#endif
