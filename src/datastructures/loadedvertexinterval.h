#ifndef LOADEDVERTEXINTERVAL_H
#define LOADEDVERTEXINTERVAL_H

#include <string>
#include <sstream>

#include "../utilities/globalDefinitions.hpp"

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
	LoadedVertexInterval(int partitionID);

  // Small methods should be inlined and given the implementation here (no linking needed)
	// Getters 
	int getFirstVertex();
	int getLastVertex();
	int getIndexStart();
	int getIndexEnd();
	int getPartitionID();

	bool hasNewEdges();

	// Setters
	void setFirstVertex(int firstVertex);
	void setLastVertex(int lastVertex);
	void setIndexStart(int indexStart);
	void setIndexEnd(int indexEnd);
	void setPartitionID(int partitionID);

	void setNewEdgeAdded(bool newEdgeAdded);


	string toString();
};

#endif
