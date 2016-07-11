#ifndef RANDOMGRAPHGEN_H
#define RANDOMGRAPHGEN_H

#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../src/datastructures/vertex.h"


/**
 * Generates a vector of random vertices
 * representing a graph
 */
std::vector<Vertex> randGraph();

#endif
