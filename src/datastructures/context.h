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

class Context
{
private:
	map<string, int> parameters;
	map<string, bool> flags;
	


public:
	//constructor
	Context(int argc, char** argv);

	//getters
	int getMemBudget();
	int getNumPartitions();
	int getMaxEdges();

	bool getInsertFlag();
	bool getAlterScheduleFlag();
	//setters
	void setMemBudget(int memBudget);
	void setNumPartitions(int numPartitions);
	void setMaxEdges(int maxEdges);

	void setInsertFlag(bool flag);
	void setAlterScheduleFlag(bool flag);
};


#endif
