#ifndef PREPROC_H
#define PREPROC_H

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



class Preproc {
private:
	char *part;
	char *bpart;
	int count;
	int vitSize;
	int dataSize;
	int *vertInterTable;
	std::set<string> eRules;
	vector<string> mapInfo;
	vector<std::pair<int, string>> *data;


public:
	Preproc(char *fileName, int size);
	void makeVIT(char *fileName);
	void makePart();
	void makeBinaryPart();
	void setMapInfo(vector<string> mapInfo, std::set<char> eRules);
	~Preproc();
};


#endif
