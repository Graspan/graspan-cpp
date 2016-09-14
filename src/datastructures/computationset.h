#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include <sstream>

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	public:
	shared_ptr< vector<int> > oldEdges;		// old
	shared_ptr< vector<char> > oldVals;

	shared_ptr< vector<int> > newEdges;		// new
	shared_ptr< vector<char> > newVals;

	shared_ptr< vector<int> > oldUnewEdges;	// old U new
	shared_ptr< vector<char> > oldUnewVals;

	// VECTORS WILL STORE NEW EDGES UNTIL END OF COMPUTATION
	shared_ptr< vector<int> > deltaEdges;
	shared_ptr< vector<char> > deltaVals;

	shared_ptr< vector<int> > oUnUdEdges;
	shared_ptr< vector<char> > oUnUdVals;

	// Constructor
	ComputationSet() {}

	void initializeEdges(vector<int> &initialEdges, vector<char> &initialVals)
	{
		oldUnewEdges = std::make_shared<vector<int>>(vector<int>(initialEdges));
		oldUnewVals = std::make_shared<vector<char>>(vector<char>(initialVals));

		newEdges = std::make_shared<vector<int>>(vector<int>(initialEdges));
		newVals = std::make_shared<vector<char>>(vector<char>(initialVals));
	}

	// old getters and setters
	inline shared_ptr< vector<int> > getOldEdges() { return oldEdges; }
	inline shared_ptr< vector<char> > getOldVals() { return oldVals; }

	inline void setOldEdges(shared_ptr< vector<int> > oldEdges) { this->oldEdges = oldEdges; }
	inline void setOldVals(shared_ptr< vector<char> > oldVals) { this->oldVals = oldVals; }

	 // new getters and setters
	inline shared_ptr< vector<int> > getNewEdges() { return newEdges; }
	inline shared_ptr< vector<char> > getNewVals() { return newVals; }

	inline void setNewEdges(shared_ptr< vector<int> > newEdges) { this->newEdges = newEdges; }
	inline void setNewVals(shared_ptr< vector<char> > newVals) { this->newVals = newVals; }

/*
	void setNewEdges(vector<int> &initialEdges) // for setting initial edges
	{ 
		shared_ptr< vector<int> > tempptr(new vector<int>(initialEdges));
		newEdges = tempptr;
	}
	void setNewVals(vector<char> &initialVals)
	{
		shared_ptr< vector<char> > tempptr(new vector<char>(initialVals));
		newVals = tempptr;
	}
*/

	// old U new getters and setters
	inline shared_ptr< vector<int> > getoldUnewEdges() { return oldUnewEdges; }
	inline shared_ptr< vector<char> > getoldUnewVals() { return oldUnewVals; }

	inline void setoldUnewEdges(shared_ptr< vector<int> > oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
	inline void setoldUnewVals(shared_ptr< vector<char> > oldUnewVals) { this->oldUnewVals = oldUnewVals; }

/*
	void setoldUnewEdges(vector<int> &initialEdges)
	{
		shared_ptr< vector<int> > tempptr(new vector<int>(initialEdges));
		oldUnewEdges = tempptr;
	}
	void setoldUnewVals(vector<char> &initialVals)
	{
		shared_ptr< vector<char> > tempptr(new vector<char>(initialVals));
		oldUnewVals = tempptr;
	}
*/

	// THESE VECTORS STORE NEW EDGES UNTIL END OF COMPUTATION
	// delta getters and setters
	inline shared_ptr< vector<int> > getDeltaEdges() { return deltaEdges; }
	inline shared_ptr< vector<char> > getDeltaVals() { return deltaVals; }

	inline void setDeltaEdges(shared_ptr< vector<int> > deltaEdges) { this->deltaEdges = deltaEdges; }
	inline void setDeltaVals(shared_ptr< vector<char> > deltaVals) { this->deltaVals = deltaVals; }

	// old U new U delta getters and setters
	inline shared_ptr< vector<int> > getoUnUdEdges() { return oUnUdEdges; }
	inline shared_ptr< vector<char> > getoUnUdVals() { return oUnUdVals; }

	inline void setoUnUdEdges(shared_ptr< vector<int> > oUnUdEdges) { this->oUnUdEdges = oUnUdEdges; }
	inline void setoUnUdVals(shared_ptr< vector<char> > oUnUdVals) { this->oUnUdVals = oUnUdVals; }


	string oldString();
	string newString();
	string oUnString();
	string deltString();
	string oUnUdString();
};

#endif
