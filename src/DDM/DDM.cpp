#include "DDM.h"

DDM::DDM() {
  // the intial vector should be reserved quite big to accomondate for repartitioning
  max_size = 1000;
  
  ddmMap.assign(max_size,vector<double>(max_size,0));
}

DDM::~DDM(){}

//the meaning of adjust p is to set teminate_map[p][] and teminate_map[][p] into UNMARK
void DDM::adjust(partitionid_t p){
  for(int i=0;i<ddmMap[p].size();i++)
    ddmMap[p][i] = 0;
  for(int i=0;i<ddmMap.size();i++)
	ddmMap[i][p] = 0;
}

//return false if the whole system should terminate
bool DDM::nextPartitionPair(partitionid_t &p, partitionid_t &q) {

  //TODO: we want to favor the current loaded partition in memory: how to express that? (i.e., add bonus to the score)
  double max = 0.0;

  for (int i = 0; i < numPartition; ++i) {
    for (int j = 0; j < numPartition; ++j ) {
      if (max < ddmMap[i][j]){
        max=ddmMap[i][j];
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
	ddmMap.resize(numPartition);
	for (int i = 0; i < numPartition; ++i)
		ddmMap[i].resize(numPartition, 0);
}

bool DDM::load_DDM(){
	std::ifstream fin;
	fin.open("../resources/DDM");
	if(!fin){
		cout << "can't read file" << endl;
		return false;
	}

	fin >> numPartition;
	enlarge();
	for(int i=0;i<numPartition;i++){
		for(int j=0;j<numPartition;j++){
			fin >> ddmMap[i][j];
		}
	}
	fin.close();
	
	return true;
}
bool DDM::save_DDM(){
	std::ofstream fout;
	fout.open("../resources/DDM");
	if(!fout){
		cout << "can't make file" << endl;
		return false;
	}

	//store numPartition
	fout << numPartition << endl;
	for(int i=0;i<numPartition;i++){
		for(int j=0;j<numPartition;j++){
		
			fout << ddmMap[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();

	return true;
}

string DDM::toString() {
	std::stringstream output;

	for (int i = 0; i < numPartition; i++) {
		for (int j = 0; j < numPartition; j++) {
			if (i != j)
				output << endl << "Partition p : " << i << "  Partition q : " << j << "  rate : " << ddmMap[i][j] << endl;
		}
	}
	return output.str();
}
