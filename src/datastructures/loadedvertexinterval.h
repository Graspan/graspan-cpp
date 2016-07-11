#ifndef LOADEDVERTEXINTERVAL_H
#define LOADEDVERTEXINTERVAL_H

#include <string>
#include <sstream>

class LoadedVertexInterval 
{
	int firstVertex;
	int lastVertex;
	int indexStart;
	int indexEnd;
	int partitionID;

	// If new edge added to partition after loaded but before saved
	bool newEdgeAdded;
	// If a new edge added to partition in current round
	bool newEdgeAddedCurrRound;

	public:
	// Constructor
	LoadedVertexInterval(int firstVertex, int lastVertex, int partitionID);

	// Getters
	int getFirstVertex();
	int getLastVertex();
	int getIndexStart();
	int getIndexEnd();
	int getPartitionID();

	bool hasNewEdges();
	bool hasNewEdgesCurrRound();

	// Setters
	void setFirstVertex(int firstVertex);
	void setLastVertex(int lastVertex);
	void setIndexStart(int indexStart);
	void setIndexEnd(int indexEnd);
	void setPartitionID(int partitionID);

	void setNewEdgeAdded(bool newEdgeAdded);
	void setNewEdgeAddedCurrRound(bool newEdgeCurrRound);


	std::string toString();
};

#endif
