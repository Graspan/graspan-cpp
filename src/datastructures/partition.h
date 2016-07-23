#ifndef PARTITION_H
#define PARTITION_H

#include <sstream>

#include "../datastructures/vertex.h"
#include "../datastructures/vit.h"
#include "../datastructures/context.h"

class Partition
{
private:
	partitionid_t id;
	int numVertices;
	int numEdges;
  bool newEdges;

	vector<Vertex> data;
	//for check partition exists. it is for repartition part ???? the fact you have obj means it exists already
	bool exist;
		
public:
	//Constructors
	Partition() { this->exist = true; newEdges = false;};
	Partition(int id, int numVertices, int numEdges, vector<Vertex> data);

  // Again, all small methods should be inlined
	//Getters
	int getID();
	int getNumVertices();
	int getNumEdges();
	vector<Vertex> &getData();
	bool getExist();

  inline bool hasNewEdges() {
    return newEdges;
  }

	//Setters
	void setID(int id);
	void setNumVertices(int numVertices);
	void setNumEdges(int numEdges);
	void setData(vector<Vertex> data);
	void setExist(bool exist);
  inline void setNewEdges(bool val) {
    newEdges = val;
  }

	//if user want save the partition to the disk use this function
	//readable == true then text format, readable == false binary format
	static void writeToFile(Partition& part, bool readable = false);

	//read the partition from the harddisk
	static void loadFromFile(int id, Partition &part, bool readable = false);

	string toString();

	// ddr = destination distribution ratio, i.e., a cell in DDM
	void calc_ddr(Context &context);
};


#endif
