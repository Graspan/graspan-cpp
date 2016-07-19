#include "computationset.h"

// constructor
ComputationSet::ComputationSet() {}

// old getters and setters
vector<int> &ComputationSet::getOldEdges() { return oldEdges; }
vector<char> &ComputationSet::getOldVals() { return oldVals; }

void ComputationSet::setOldEdges(vector<int> &oldEdges) { this->oldEdges = oldEdges; }
void ComputationSet::setOldVals(vector<char> &oldVals) { this->oldVals = oldVals; }


// new getters and setters
vector<int> &ComputationSet::getNewEdges() { return newEdges; }
vector<char> &ComputationSet::getNewVals() { return newVals; }

void ComputationSet::setNewEdges(vector<int> &newEdges) { this->newEdges = newEdges; }
void ComputationSet::setNewVals(vector<char> &newVals) { this->newVals = newVals; }


// old U new getters and setters
vector<int> &ComputationSet::getoldUnewEdges() { return oldUnewEdges; }
vector<char> &ComputationSet::getoldUnewVals() { return oldUnewVals; }

void ComputationSet::setoldUnewEdges(vector<int> &oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
void ComputationSet::setoldUnewVals(vector<char> &oldUnewVals) { this->oldUnewVals = oldUnewVals; }
