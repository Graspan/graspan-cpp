#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <utility>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../mapping/grammar.h"
#include "edgemerger.h"
#include "../utilities/globalDefinitions.hpp"

//struct IDValuePair {
//	int id;
//	char val;
//
//	bool operator==(const IDValuePair &pair) const { return pair.id == id && pair.val == val; }
//}; 
//
//struct Hash {
//	size_t operator()(const IDValuePair &pair) const { return 31 * pair.id + 1; }
//};

long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Grammar &gram);

#endif
