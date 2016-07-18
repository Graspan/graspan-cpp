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

class Repart {
private:
public:
	static void repartition(Partition &p1, Partition &p2);


};

#endif
