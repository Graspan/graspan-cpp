#ifndef DDM_H
#define DDM_H
//where is my #ifndef and #def?

#include "../utilities/globalDefinitions.hpp"
#include <iostream>
#include "DDM_map.h"
// There should be only one DDM object in the whole execution
// ==> implement Singleton pattern

class DDM{
 private:
  //TODO: merge these two vectors into 1
  //TODO: implement scheduling policy described in the paper
  int max_size;
  DDM_map temp_info;  //for store percentage and terminate
  vector<vector<DDM_map> > ddmMap; //array for storing ddmInfo
	int numPartition;

 public:
  
  //default constructor, the numPartition should be obtained thru the Context object
  DDM(); 
  DDM(int numPartition); 
	~DDM();

  //small methods should be inlined for efficiency
	inline void set(partitionid_t p, partitionid_t q, double rate) {
    ddmMap[p][q].partitionRate = rate;
  }
	void adjust(int p);

	inline void markTerminate(partitionid_t p, partitionid_t q) {
    ddmMap[p][q].terminate_map = true;
  }

  // the indices p and q tell which partitionRate[p][q] is max: i.e., this is our scheduler
  // the bool return value indicate whether or not we should terminate the whole system
  bool nextPartitionPair(int& p, int &q);

  // if repartitioning happens, 1 or 2 new partition can happen, that means DDM needs to be enlarged
  // you should figure out how to implement this resizing logic efficiently
  void enlarge();
  
};

#endif
