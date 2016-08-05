#ifndef REPART_H
#define REPART_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <set>

#include "../utilities/globalDefinitions.hpp"
#include "../datastructures/partition.h"
#include "../datastructures/vertex.h"
#include "../datastructures/context.h"
#include "../datastructures/loader.h"

class Repart {
private:
public:
	//p1 is exceeded partition and p2 is new partition
	static void repartition(Partition &p1, Partition &p2, Context &context);
	static void run(Partition &p1, Partition &p2, Context &context, bool newEdgesInP, bool newEdgesInQ, bool terminate);

};

#endif
