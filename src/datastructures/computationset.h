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


	public:
	// Constructor
	ComputationSet() {}

  //TODO: Small methods should be inlined 

	// old getters and setters
	inline vector<int> &getOldEdges() { return oldEdges; }
	inline vector<char> &getOldVals() { return oldVals; }

	inline void setOldEdges(vector<int> &oldEdges) { this->oldEdges = oldEdges;
	inline void setOldVals(vector<char> &oldVals) { this->oldVals = oldVals;
	 
	 // new getters and setters
	inline vector<int> &getNewEdges() { return newEdges; }
	inline vector<char> &getNewVals() { return newVals; }

	inline void setNewEdges(vector<int> &newEdges) { this->nwEdges = newEdges; }
	inline void setNewVals(vector<char> &newVals) { this->newVals = newVals; }

	// old U new getters and setters
	inline vector<int> &getoldUnewEdges() { return oldUnewEdges; }
	inline vector<char> &getoldUnewVals() { return oldUnewVals; }

	inline void setoldUnewEdges(vector<int> &oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
	inline void setoldUnewVals(vector<char> &oldUnewVals) { this->oldUnewVals = oldUnewVals; }
};

#endif
