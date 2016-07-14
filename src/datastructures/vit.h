#ifndef VIT_H
#define VIT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../utilities/globalDefinitions.hpp"

class VIT
{
private:

	// each entry is pair of [low, high] of vertices in the partition
	vector<pair<vertexid_t, vertexid_t>> vit;

public:
	//Constructors
	VIT() {};
	VIT(vector<pair<int, int>> vit);
	

	//Getters
	vector<pair<int, int>> getVIT();
	int getStart(int pid);
	int getEnd(int pid);

	//Setters
	void setVIT(vector<pair<int, int>> vit);

	// given a vertex id, return true if this vertex is in partition pid
	bool is_in_partition(vertexid_t vid, partitionid_t pid);

	// return the partition id which vetex vid is in
	int partition(vertexid_t vid);

	// when partition whose id is partition_id is repartitioned, its VIT entry needs to be changed
	// also VIT adds new entry for the newly-created partition
	//void modify(partitionid_t pid); 

	static void writeToFile(VIT& vit);

	static VIT loadFromFile(char* filename) ;
	
};


#endif
