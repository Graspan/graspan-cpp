#ifndef VIT_H
#define VIT_H

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "../utilities/globalDefinitions.hpp"

class VIT
{
private:

	// each entry is pair of [low, high] of vertices in the partition
	vector<pair<vertexid_t, vertexid_t>> vit;
	vector<int> degree; // what's this? number of edges per partition?

public:
	//Constructors
	VIT() {};
	

	//Getters
	vector<pair<vertexid_t, vertexid_t>> &getVIT();
	int getStart(int pid);
	int getEnd(int pid);
	vector<int> &getDegree();
	int getDegree(int pid);
	int getNumVertex(); // TODO: rename this, this is misleading; it eturns vit.size()

	//Setters
	void setVIT(vector<pair<int, int>> vit);
	void setDegree(int numPartition);

	//change the vit[id] values
	void setVITID(int id, vertexid_t start, vertexid_t end);

	// given a vertex id, return true if this vertex is in partition pid
	bool is_in_partition(vertexid_t vid, partitionid_t pid);

	// return the partition id which vetex vid is in
	int partition(vertexid_t vid);

  string toString();

	// TODO:when partition whose id is partition_id is repartitioned, its VIT entry needs to be changed
	// also VIT adds new entry for the newly-created partition
	//void modify(partitionid_t pid); 

	bool writeToFile(string fname);

	bool loadFromFile(string fname);
	
};


#endif
