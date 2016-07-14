#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <set>

#include "../datastructures/vertex.h"
#include "../datastructures/partition.h"
#include "../utilities/globalDefinitions.hpp"



class Loader {
private:
public:
	Partition loadBinary(char *fileName, int id);
	//static Partition loadPartition(int id, bool readable = false) {};
	//graphname
		//graphname.partition.1.b
		//graphname.partition.1.h
};


#endif