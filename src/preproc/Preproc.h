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



class Preproc {
private:
	char *part;
	char *bpart;
	int count;
	int vitSize;
	int dataSize;
	int *vertInterTable;
	std::set<std::string> eRules;
	std::vector<std::string> mapInfo;
	std::vector<std::pair<int, std::string>> *data;


public:
	Preproc(char *fileName, int size);
	void makeVIT(char *fileName);
	void makePart(bool input);
	void makeBinaryPart(bool input);
	void setMapInfo(std::vector<std::string> mapInfo, std::set<char> eRules);
	~Preproc();
};


#endif
