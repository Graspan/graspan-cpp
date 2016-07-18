#include "DDM.h"

DDM::DDM(int numPartition){
	this->numPartition = numPartition;
	originNumPartition = numPartition;
	partitionRate.assign(this->numPartition,vector<double>(this->numPartition,0));
	terminate_map.assign(this->numPartition,vector<int>(this->numPartition,UNMARK));
}

DDM::~DDM(){}

void DDM::set(int p,int q,double rate){
	partitionRate[p][q] = rate;
}

//if using this func, you should divide 2 int value
long DDM::nextPartitionPart(){
	double max=0;
	long store_part;	//store partition

	for(int i=0;i<partitionRate.size();i++){
		for(int j=0;j<partitionRate[i].size();j++){
			if(max<partitionRate[i][j]){
				max=partitionRate[i][j];
				store_part = i << 32 | j;
			}
		}
	}
	return store_part;
}

void DDM::adjust(int p){
	numPartition++;
	partitionRate.resize(numPartition,vector<double>(originNumPartition,0));
	terminate_map.resize(numPartition,vector<int>(originNumPartition,UNMARK));
}

void DDM::markTerminate(int p,int q){
	terminate_map[p][q] = MARK;
}
