#ifndef LOADER_H
#define LOADER_H

#include "../datastructures/vertex.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <set>



class Loader {
private:
	char *part;
	char *bpart;
	std::vector<Vertex> testt;
public:
	void loadBinary(char *fileName);
	std::vector<Vertex> getData();
};


#endif