#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include <sstream>

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	public:
	unique_ptr< vector<int> > oldEdges;		// old
	unique_ptr< vector<char> > oldVals;

	unique_ptr< vector<int> > newEdges;		// new
	unique_ptr< vector<char> > newVals;

	unique_ptr< vector<int> > oldUnewEdges;	// old U new
	unique_ptr< vector<char> > oldUnewVals;

	// VECTORS WILL STORE NEW EDGES UNTIL END OF COMPUTATION
	unique_ptr< vector<int> > deltaEdges;
	unique_ptr< vector<char> > deltaVals;

	unique_ptr< vector<int> > oUnUdEdges;
	unique_ptr< vector<char> > oUnUdVals;

	// Constructor
	ComputationSet() {}

	void initializeEdges(vector<int> &initialEdges, vector<char> &initialVals)
	{
		oldUnewEdges = make_unique<vector<int>>(vector<int>(initialEdges));
		oldUnewVals = make_unique<vector<char>>(vector<char>(initialVals));

		newEdges = make_unique<vector<int>>(vector<int>(initialEdges));
		newVals = make_unique<vector<char>>(vector<char>(initialVals));
	}

	// old getters and setters
	inline unique_ptr< vector<int> > &getOldEdges() { return oldEdges; }
	inline unique_ptr< vector<char> > &getOldVals() { return oldVals; }

	inline void setOldEdges(unique_ptr< vector<int> > &oldEdges) { this->oldEdges = std::move(oldEdges); }
	inline void setOldVals(unique_ptr< vector<char> > &oldVals) { this->oldVals = std::move(oldVals); }

	 // new getters and setters
	inline unique_ptr< vector<int> > &getNewEdges() { return newEdges; }
	inline unique_ptr< vector<char> > &getNewVals() { return newVals; }

	inline void setNewEdges(unique_ptr< vector<int> > &newEdges) { this->newEdges = std::move(newEdges); }
	inline void setNewVals(unique_ptr< vector<char> > &newVals) { this->newVals = std::move(newVals); }

	// old U new getters and setters
	inline unique_ptr< vector<int> > &getoldUnewEdges() { return oldUnewEdges; }
	inline unique_ptr< vector<char> > &getoldUnewVals() { return oldUnewVals; }

	inline void setoldUnewEdges(unique_ptr< vector<int> > &oldUnewEdges) { this->oldUnewEdges = std::move(oldUnewEdges); }
	inline void setoldUnewVals(unique_ptr< vector<char> > &oldUnewVals) { this->oldUnewVals = std::move(oldUnewVals); }


	// THESE VECTORS STORE NEW EDGES UNTIL END OF COMPUTATION
	// delta getters and setters
	inline unique_ptr< vector<int> > &getDeltaEdges() { return deltaEdges; }
	inline unique_ptr< vector<char> > &getDeltaVals() { return deltaVals; }

	inline void setDeltaEdges(unique_ptr< vector<int> > &deltaEdges) { this->deltaEdges = std::move(deltaEdges); }
	inline void setDeltaVals(unique_ptr< vector<char> > &deltaVals) { this->deltaVals = std::move(deltaVals); }

	// old U new U delta getters and setters
	inline unique_ptr< vector<int> > &getoUnUdEdges() { return oUnUdEdges; }
	inline unique_ptr< vector<char> > &getoUnUdVals() { return oUnUdVals; }

	inline void setoUnUdEdges(unique_ptr< vector<int> > &oUnUdEdges) { this->oUnUdEdges = std::move(oUnUdEdges); }
	inline void setoUnUdVals(unique_ptr< vector<char> > &oUnUdVals) { this->oUnUdVals = std::move(oUnUdVals); }


	string oldString();
	string newString();
	string oUnString();
	string deltString();
	string oUnUdString();
};

#endif
