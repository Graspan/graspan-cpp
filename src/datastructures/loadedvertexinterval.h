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
	inline int getFirstVertex() { return firstVertex; }
	inline int getLastVertex() { return lastVertex; }
	inline int getIndexStart() { return indexStart; }
	inline int getIndexEnd() { return indexEnd; }
	inline int getPartitionID() { return partitionID; }

	inline bool hasNewEdges() { return newEdgeAdded; }

	// Setters
	inline void setFirstVertex(int firstVertex) { this->firstVertex = firstVertex; }
	inline void setLastVertex(int lastVertex) { this->lastVertex = lastVertex; }
	inline void setIndexStart(int indexStart) { this->indexStart = indexStart; }
	inline void setIndexEnd(int indexEnd) { this->indexEnd = indexEnd; }
	inline void setPartitionID(int partitionID) { this->partitionID = partitionID; }

	inline void setNewEdgeAdded(bool newEdgeAdded) { this->newEdgeAdded = newEdgeAdded; }


	string toString();
};

#endif
