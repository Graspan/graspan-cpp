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
	//if user want to load the partition from the disk and save on the p
	//use this function id is partition id, p is where you going to save on memory
	//readable is text and readable == false is binary format file
	static bool loadPartition(int id, Partition &p, bool readable = false);
	//graphname
		//graphname.partition.1.b
		//graphname.partition.1.h
};


#endif
