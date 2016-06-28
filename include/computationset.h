#ifndef COMPUTATIONSET_H
#define COMPUTATIONSET_H

#include <iostream>
#include <vector>

class ComputationSet
{
	std::vector<int> oldEdges;		// old
	std::vector<char> oldVals;

	std::vector<int> newEdges;		// new
	std::vector<char> newVals;

	std::vector<int> oldUnewEdges;	// old U new
	std::vector<char> oldUnewVals;

	std::vector<int> deltaEdges;	// delta
	std::vector<char> deltaVals;

	std::vector<int> oldUnewUdeltaEdges;	// old U new U delta
	std::vector<char> oldUnewUdeltaVals;

		

	public:
	// Constructor
	ComputationSet();

	// old getters and setters
	std::vector<int> getOldEdges();	
	std::vector<char> getOldVals();

	void setOldEdges(std::vector<int> oldEdges);
	void setOldVals(std::vector<char> oldVals);
	
	// new getters and setters
	std::vector<int> getNewEdges();
	std::vector<char> getNewVals();

	void setNewEdges(std::vector<int> newEdges);
	void setNewVals(std::vector<char> newVals);

	// old U new getters and setters
	std::vector<int> getoldUnewEdges();
	std::vector<char> getoldUnewVals();

	void setoldUnewEdges(std::vector<int> oldUnewEdges);
	void setoldUnewVals(std::vector<char> oldUnewVals);

	// delta getters and setters
	std::vector<int> getDeltaEdges();
	std::vector<char> getDeltaVals();

	void setDeltaEdges(std::vector<int> deltaEdges);
	void setDeltaVals(std::vector<char> deltaVals);

	// old U new U delta getters and setters
	std::vector<int> getoldUnewUdeltaEdges();
	std::vector<char> getoldUnewUdeltaVals();

	void setoldUnewUdeltaEdges(std::vector<int> oUnUdEdges);
	void setoldUnewUdeltaVals(std::vector<char> oUnUdVals);
};

#endif
