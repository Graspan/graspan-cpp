#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <utility>

#include "edgemerger.h"
#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../mapping/grammar.h"
#include "../utilities/globalDefinitions.hpp"


long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Grammar &gram);

#endif
