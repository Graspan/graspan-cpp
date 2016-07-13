#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include <iostream>
#include <vector>

#include "../utilities/globalDefinitions.hpp"

class ComputationSet
{
	vector<int> oldEdges;		// old
	vector<char> oldVals;

	vector<int> newEdges;		// new
	vector<char> newVals;

	vector<int> oldUnewEdges;	// old U new
	vector<char> oldUnewVals;

	vector<int> deltaEdges;	// delta
	vector<char> deltaVals;

	vector<int> oldUnewUdeltaEdges;	// old U new U delta
	vector<char> oldUnewUdeltaVals;

		

	public:
	// Constructor
	ComputationSet();

	// old getters and setters
	vector<int> getOldEdges();	
	vector<char> getOldVals();

	void setOldEdges(vector<int> oldEdges);
	void setOldVals(vector<char> oldVals);
	
	// new getters and setters
	vector<int> getNewEdges();
	vector<char> getNewVals();

	void setNewEdges(vector<int> newEdges);
	void setNewVals(vector<char> newVals);

	// old U new getters and setters
	vector<int> getoldUnewEdges();
	vector<char> getoldUnewVals();

	void setoldUnewEdges(vector<int> oldUnewEdges);
	void setoldUnewVals(vector<char> oldUnewVals);

	// delta getters and setters
	vector<int> getDeltaEdges();
	vector<char> getDeltaVals();

	void setDeltaEdges(vector<int> deltaEdges);
	void setDeltaVals(vector<char> deltaVals);

	// old U new U delta getters and setters
	vector<int> getoldUnewUdeltaEdges();
	vector<char> getoldUnewUdeltaVals();

	void setoldUnewUdeltaEdges(vector<int> oUnUdEdges);
	void setoldUnewUdeltaVals(vector<char> oUnUdVals);
};

#endif
