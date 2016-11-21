CC=g++ -std=c++0x

# will eventually need to use threads
#CFLAGS=-ggdb -fopenmp -O2
CFLAGS=-lboost_thread -O3 -ggdb

##### source files #####
# preprocessing
PREP=preproc/preproc.cpp preproc/preproc_new.cpp preproc/run_pre.cpp
# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/edgemerger.cpp edgecomp/repart.cpp
LOADER=datastructures/loader.cpp edgecomp/grammar.cpp
# computation sets included through header files
DATASTRUCTS=datastructures/vertex.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp datastructures/partition.cpp datastructures/context.cpp datastructures/vit.cpp datastructures/DDM.cpp
UTIL=../test/timer.cpp Library/Logger.cpp




##### build rules #####
comp: dispatcher/graspan.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL)
	$(CC) $(CFLAGS) dispatcher/graspan.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL) -o ../bin/comp

