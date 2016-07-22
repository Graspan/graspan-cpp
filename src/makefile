CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread


##### source files #####
# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/edgemerger.cpp edgecomp/repart.cpp
LOADER=datastructures/loader.cpp edgecomp/grammar.cpp
DATASTRUCTS=datastructures/vertex.cpp datastructures/computationset.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp datastructures/partition.cpp datastructures/context.cpp datastructures/vit.cpp datastructures/DDM.cpp
TEST=../test/timer.cpp


##### build rules #####
all: comp

# prepessing
#prep: $(PREPROC)
#	$(CC) $(PREPROC) -o ../bin/prep

# edge computation program
comp: dispatcher/graspan.cpp $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(TEST)
	$(CC) -ggdb dispatcher/graspan.cpp $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(TEST) -o ../bin/comp

