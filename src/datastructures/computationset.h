#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	vector<int> oldEdges;		// old
	vector<char> oldVals;

	vector<int> newEdges;		// new
	vector<char> newVals;

	vector<int> oldUnewEdges;	// old U new
	vector<char> oldUnewVals;

	// TEMP until better solution
	vector<int> deltaEdges;
	vector<char> deltaVals;

	vector<int> oUnUdEdges;
	vector<char> oUnUdVals;


	public:
	// Constructor
	ComputationSet() {}

  //TODO: Small methods should be inlined 

	// old getters and setters
	inline vector<int> &getOldEdges() { return oldEdges; }
	inline vector<char> &getOldVals() { return oldVals; }

	inline void setOldEdges(vector<int> &oldEdges) { this->oldEdges = oldEdges; }
	inline void setOldVals(vector<char> &oldVals) { this->oldVals = oldVals; }
	 
	 // new getters and setters
	inline vector<int> &getNewEdges() { return newEdges; }
	inline vector<char> &getNewVals() { return newVals; }

	inline void setNewEdges(vector<int> &newEdges) { this->newEdges = newEdges; }
	inline void setNewVals(vector<char> &newVals) { this->newVals = newVals; }

	// old U new getters and setters
	inline vector<int> &getoldUnewEdges() { return oldUnewEdges; }
	inline vector<char> &getoldUnewVals() { return oldUnewVals; }

	inline void setoldUnewEdges(vector<int> &oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
	inline void setoldUnewVals(vector<char> &oldUnewVals) { this->oldUnewVals = oldUnewVals; }

	// TEMP until better solution
	// delta getters and setters
	inline vector<int> &getDeltaEdges() { return deltaEdges; }
	inline vector<char> &getDeltaVals() { return deltaVals; }

	inline void setDeltaEdges(vector<int> &deltaEdges) { this->deltaEdges = deltaEdges; }
	inline void setDeltaVals(vector<char> &deltaVals) { this->deltaVals = deltaVals; }

	// old U new U delta getters and setters
	inline vector<int> &getoUnUdEdges() { return oUnUdEdges; }
	inline vector<char> &getoUnUdVals() { return oUnUdVals; }

	inline void setoUnUdEdges(vector<int> &oUnUdEdges) { this->oUnUdEdges = oUnUdEdges; }
	inline void setoUnUdVals(vector<char> &oUnUdVals) { this->oUnUdVals = oUnUdVals; }
};

#endif
