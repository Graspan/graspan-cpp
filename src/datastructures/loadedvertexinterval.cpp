#include "loadedvertexinterval.h"

// Constructor
LoadedVertexInterval::LoadedVertexInterval(int partitionID)
{
	this->partitionID = partitionID;
}


// string representation
string LoadedVertexInterval::toString()
{
	std::stringstream output;

	output << endl << "(PartID: " << partitionID << ", VRange: " << firstVertex << " - " << lastVertex << ", IDRange: " << indexStart << " - " << indexEnd << ")";

	return output.str();
}
