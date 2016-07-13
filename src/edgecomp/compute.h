#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <unordered_set>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "grammarchecker.h"
#include "edgemerger.h"
#include "../utilities/globalDefinitions.hpp"

struct IDValuePair {
	int id;
	char val;

	bool operator==(const IDValuePair &pair) const { return pair.id == id && pair.val == val; }
}; 

struct Hash {
	size_t operator()(const IDValuePair &pair) const { return 1 * 31 + pair.id; }
};

long updateEdges(int i, ComputationSet compSets[], vector<LoadedVertexInterval> &intervals);

#endif
