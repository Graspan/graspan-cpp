#include "DDM.h"

DDM::DDM() {
  //to be implemented
  // the intial vector should be reserved quite big to accomondate for repartitioning

}

DDM::DDM(int numPartition){
	this->numPartition = numPartition;
	originNumPartition = numPartition;
	partitionRate.assign(this->numPartition,vector<double>(this->numPartition,0));
	terminate_map.assign(this->numPartition,vector<int>(this->numPartition,UNMARK));
}

DDM::~DDM(){}

//void DDM::set(int p, int q, double rate){
//	partitionRate[p][q] = rate;
//}

//if using this func, you should divide 2 int value -- bad way to do this
long DDM::nextPartitionPart(){
	double max=0;
	long store_part=0;	//store partition

	for(int i=0;i<partitionRate.size();i++){
		for(int j=0;j<partitionRate[i].size();j++){
			if(max<partitionRate[i][j]){
				max=partitionRate[i][j];
				store_part = ((long)i << 32) | j; // cast to long first otherwise you will delete value of i
			}
		}
	}
	return store_part;
}

void DDM::adjust(partitionid_t p){
	//numPartition++;
	//partitionRate.resize(numPartition,vector<double>(originNumPartition,0));
	//terminate_map.resize(numPartition,vector<int>(originNumPartition,UNMARK));

  //this is not correct - the meaning of adjust p is to set teminate_map[p][] and teminate_map[][p] into UNMARK
}

//return false iff the whole system should terminate
bool DDM::nextPartitionPair(partitionid_t &p, partitionid_t &q) {

  //TODO: we want to favor the current loaded partition in memory: how to express that? (i.e., add bonus to the score)
  double max = 0.0;

  for (int i = 0; i < numPartition; ++i) {
    for (int j = 0; j < numPartition; ++j ) {
      if (max < partitionRate[i][j]){
        max=partitionRate[i][j];
        p = i;
        q = j;
      }
    }

  }

  if (max == 0.0) { // should terminate since every cell is either 0 or negative -- we assume a pair is done when its partitionRate is negative
    return false;
  }
  
  return true;
}

void DDM::enlarge() {
  //to be implemented
}

