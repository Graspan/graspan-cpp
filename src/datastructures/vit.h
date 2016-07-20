#ifndef VIT_H
#define VIT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string>
#include <string.h>

#include "../utilities/globalDefinitions.hpp"

class VIT
{
private:

	// each entry is pair of [low, high] of vertices in the partition
	vector<pair<vertexid_t, vertexid_t>> vit;
	int *degree;

public:
	//Constructors
	VIT() {};
	VIT(vector<pair<int, int>> vit);
	

	//Getters
	vector<pair<vertexid_t, vertexid_t>> &getVIT();
	int getStart(int pid);
	int getEnd(int pid);
	int *getDegree();
	int getDegree(int pid);

	//Setters
	void setVIT(vector<pair<int, int>> vit);
	void setDegree(int numPartition);

	//change the vit[id] values
	void setVITID(int id, vertexid_t start, vertexid_t end);

	// given a vertex id, return true if this vertex is in partition pid
	bool is_in_partition(vertexid_t vid, partitionid_t pid);

	// return the partition id which vetex vid is in
	int partition(vertexid_t vid);

	// when partition whose id is partition_id is repartitioned, its VIT entry needs to be changed
	// also VIT adds new entry for the newly-created partition
	//void modify(partitionid_t pid); 

	static void writeToFile(VIT& v);

	static void loadFromFile(VIT &v) ;
	
};


#endif
