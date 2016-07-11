#include "../../include/computationset.h"

// constructor
ComputationSet::ComputationSet() {}

// old getters and setters
std::vector<int> ComputationSet::getOldEdges() { return oldEdges; }
std::vector<char> ComputationSet::getOldVals() { return oldVals; }

void ComputationSet::setOldEdges(std::vector<int>  oldEdges) { this->oldEdges = oldEdges; }
void ComputationSet::setOldVals(std::vector<char> oldVals) { this->oldVals = oldVals; }


// new getters and setters
std::vector<int> ComputationSet::getNewEdges() { return newEdges; }
std::vector<char> ComputationSet::getNewVals() { return newVals; }

void ComputationSet::setNewEdges(std::vector<int>  newEdges) { this->newEdges = newEdges; }
void ComputationSet::setNewVals(std::vector<char> newVals) { this->newVals = newVals; }


// old U new getters and setters
std::vector<int> ComputationSet::getoldUnewEdges() { return oldUnewEdges; }
std::vector<char> ComputationSet::getoldUnewVals() { return oldUnewVals; }

void ComputationSet::setoldUnewEdges(std::vector<int>  oldUnewEdges) { this->oldUnewEdges = oldUnewEdges; }
void ComputationSet::setoldUnewVals(std::vector<char> oldUnewVals) { this->oldUnewVals = oldUnewVals; }


// delta getters and setters
std::vector<int> ComputationSet::getDeltaEdges() { return deltaEdges; }
std::vector<char> ComputationSet::getDeltaVals() { return deltaVals; }

void ComputationSet::setDeltaEdges(std::vector<int>  deltaEdges) { this->deltaEdges = deltaEdges; }
void ComputationSet::setDeltaVals(std::vector<char> deltaVals) { this->deltaVals = deltaVals; }


// old U new U delta getters and setters
std::vector<int> ComputationSet::getoldUnewUdeltaEdges() { return oldUnewUdeltaEdges; }
std::vector<char> ComputationSet::getoldUnewUdeltaVals() { return oldUnewUdeltaVals; }

void ComputationSet::setoldUnewUdeltaEdges(std::vector<int>  oUnUdEdges) { this->oldUnewUdeltaEdges = oUnUdEdges; }
void ComputationSet::setoldUnewUdeltaVals(std::vector<char> oUnUdVals) { this->oldUnewUdeltaVals = oUnUdVals; }
