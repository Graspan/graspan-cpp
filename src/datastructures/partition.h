#ifndef PARTITION_H
#define PARTITION_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../utilities/globalDefinitions.hpp"
#include "../datastructures/vertex.h"
#include "../datastructures/vit.h"

class Partition
{
private:
	partitionid_t id;
	int numVertices;
	int numEdges;

	vector<Vertex> data;
		
public:
	//Constructors
	Partition() {};
	Partition(int id, int numVertices, int numEdges, vector<Vertex> data);

	//Getters
	int getID();
	int getNumVertices();
	int getNumEdges();
	vector<Vertex> getData();

	//Setters
	void setID(int id);
	void setNumVertices(int numVertices);
	void setNumEdges(int numEdges);
	void setData(vector<Vertex> data);

	
	static void writeToFile(Partition& part, bool readable = false);

	static Partition loadFromFile();
};


#endif
