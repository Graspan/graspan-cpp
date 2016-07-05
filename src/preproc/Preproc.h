#ifndef PREPROC_H
#define PREPROC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <time.h>



class Preproc {
private:
	char *part;
	int count;
	int vitSize;
	int dataSize;
	int *vertInterTable;

	std::vector<std::pair<int, std::string>> *data;


public:
	Preproc(char *fileName, int size);
	void makeVIT(char *fileName);
	void makePart();
	~Preproc();
};


#endif