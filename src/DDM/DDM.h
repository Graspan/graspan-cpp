#ifndef DDM_H
#define DDM_H

#include "../utilities/globalDefinitions.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <vector>


class DDM{
private:
	vector<vector<double> > partitionRate; //for store percentage
	vector<vector<double> > edgeCnt; //for store number of edges of p and q
	vector<int> partitionSize; //for store total edges count
	int numPartition;
	vector<std::string> partitionName;
	void prepare(vector<int> val);
	void set();
	int findPart(int num);
public:
	DDM(string dirName);
	~DDM();
	long nextPartitionPart();
	void testPrint();
};

#endif
