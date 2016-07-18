#include <iostream>
#include <vector>

#define MARK 1
#define UNMARK 0

class DDM{
private:
	vector<vector<double> > partitionRate; //for store percentage
	vector<vector<int> > terminate_map;
	int numPartition;
	int originNumPartition;
public:
	DDM(int numPartition);
	~DDM();
	void set(int p,int q,double rate);
	long nextPartitionPart();
	void adjust(int p);
	void markTerminate(int p,int q);
};
