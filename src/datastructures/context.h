#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>

#include "../utilities/globalDefinitions.hpp"
#include "vit.h"
#include "DDM.h"
#include "../edgecomp/grammar.h"

class Context
{
private:
	unsigned long long int memBudget;
	map<string, unsigned int> parameters;
	map<string, string> filePath;
	map<string, bool> flags;
	


public:

	Grammar grammar;
	VIT vit;
	DDM ddm;

	//constructor
	//user input format is memBudget=10 numPartitions=3 insertionSort=true 
	//if user don't input data then default values are in these things
	Context(int argc, char** argv);

	//getters
	unsigned long long int getMemBudget();
	int getNumPartitions();
	int getMaxEdges();
	int getNumThreads();

	string getGraphFile();
	string getGrammarFile();


	bool getInsertFlag();
	bool getAlterScheduleFlag();
	//setters
	//void setMemBudget(int memBudget);
	void setNumPartitions(int numPartitions);
	void setMaxEdges(int maxEdges);

	void setInsertFlag(bool flag);
	void setAlterScheduleFlag(bool flag);


};


#endif
