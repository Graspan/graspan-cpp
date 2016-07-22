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
	ComputationSet();

  //TODO: Small methods should be inlined 

	// old getters and setters
	vector<int> &getOldEdges();	
	vector<char> &getOldVals();

	void setOldEdges(vector<int> &oldEdges);
	void setOldVals(vector<char> &oldVals);
	
	// new getters and setters
	vector<int> &getNewEdges();
	vector<char> &getNewVals();

	void setNewEdges(vector<int> &newEdges);
	void setNewVals(vector<char> &newVals);

	// old U new getters and setters
	vector<int> &getoldUnewEdges();
	vector<char> &getoldUnewVals();

	void setoldUnewEdges(vector<int> &oldUnewEdges);
	void setoldUnewVals(vector<char> &oldUnewVals);
};

#endif
