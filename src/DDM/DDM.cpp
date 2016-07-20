#include "DDM.h"

DDM::DDM() {
  // the intial vector should be reserved quite big to accomondate for repartitioning
  max_size = 1000;
  
  temp_info.partitionRate = temp_info.terminate_map = 0;
  ddmMap.assign(max_size,vector<DDM_map>(max_size,temp_info));
}

DDM::DDM(int numPartition){
	this->numPartition = numPartition;

	temp_info.partitionRate = temp_info.terminate_map = 0;
  ddmMap.assign(numPartition,vector<DDM_map>(numPartition,temp_info));
}

DDM::~DDM(){}

vector<vector<DDM_map> >& DDM::getDdmMap() {
	return ddmMap;
}

//the meaning of adjust p is to set teminate_map[p][] and teminate_map[][p] into UNMARK
void DDM::adjust(partitionid_t p){
  for(int i=0;i<ddmMap[p].size();i++)
      ddmMap[p][i].terminate_map = false;
  for(int i=0;i<ddmMap.size();i++)
    ddmMap[i][p].terminate_map = false;
}

//return false if the whole system should terminate
bool DDM::nextPartitionPair(partitionid_t &p, partitionid_t &q) {

  //TODO: we want to favor the current loaded partition in memory: how to express that? (i.e., add bonus to the score)
  double max = 0.0;

  for (int i = 0; i < numPartition; ++i) {
    for (int j = 0; j < numPartition; ++j ) {
      if (max < ddmMap[i][j].partitionRate){
        max=ddmMap[i][j].partitionRate;
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

void DDM::setNumPartition(int numPartition) {
	this->numPartition = numPartition;
}

void DDM::enlarge() {
  
	temp_info.partitionRate = temp_info.terminate_map = 0;

	ddmMap.resize(numPartition);
	for (int i = 0; i < numPartition; ++i)
		ddmMap[i].resize(numPartition, temp_info);
}

string DDM::toString() {
	std::stringstream output;

	for (int i = 0; i < numPartition; i++) {
		for (int j = 0; j < numPartition; j++) {
			if (i != j)
				output << endl << "Partition p : " << i << "  Partition q : " << j << "  rate : " << ddmMap[i][j].partitionRate << endl;
		}
	}
	return output.str();
}
