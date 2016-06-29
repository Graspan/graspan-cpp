#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <stdio.h>


//coded in visualstudio so need to fix to use in linux 
class Preproc {
private:
	char *part;
	char *outfileName;
	int *vertInterTable;
	std::map<int, int> vitMap;
	int vitSize;
public:
	Preproc();
	void makeVIT(char *fileName, int size = 5);
	void makePart(char *fileName);
	void partSort();
	~Preproc();
};


#endif