#ifndef LOADER_H
#define LOADER_H

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../utilities/globalDefinitions.hpp"
#include "vertex.h"
#include "partition.h"


class Loader {
private:
public:
	//if user wants to load the partition from the disk 
	//use this function, id is partition id, p is where you going to save on memory
	//readable==true means text, and false means binary format 
	static bool loadPartition(partitionid_t id, Partition &p, bool readable, Context c);
	//graphname
		//graphname.partition.1.b
		//graphname.partition.1.h
};


#endif
