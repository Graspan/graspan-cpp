#ifndef DDM_H
#define DDM_H
//where is my #ifndef and #def?

#include "../utilities/globalDefinitions.hpp"
#include <iostream>


#define MARK 1
#define UNMARK 0

// There should be only one DDM object in the whole execution
// ==> implement Singleton pattern

class DDM{
 private:
  //TODO: merge these two vectors into 1
  //TODO: implement scheduling policy described in the paper
	vector<vector<double> > partitionRate; //for store percentage
	vector<vector<int> > terminate_map; //why int instead of bool??
	int numPartition;
	int originNumPartition; //what's this for?

 public:
  
  //default constructor, the numPartition should be obtained thru the Context object
  DDM(); 
  DDM(int numPartition); 
	~DDM();

  //small methods should be inlined for efficiency
	inline void set(partitionid_t p, partitionid_t q, double rate) {
    partitionRate[p][q] = rate;
  }
	long nextPartitionPart(); // this is a bad way to return 2 values since you spent time encoding and decoding
	void adjust(int p);

	inline void markTerminate(partitionid_t p, partitionid_t q) {
    terminate_map[p][q] = MARK;
  }

  // the indices p and q tell which partitionRate[p][q] is max: i.e., this is our scheduler
  // the bool return value indicate whether or not we should terminate the whole system
  bool nextPartitionPair(int& p, int &q);

  // if repartitioning happens, 1 or 2 new partition can happen, that means DDM needs to be enlarged
  // you should figure out how to implement this resizing logic efficiently
  void enlarge();
  
};

#endif
