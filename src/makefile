CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread


##### source files #####
# prepessing
PREPROC=prep/main.cpp preproc/Preproc.cpp mapping/grammarChecker.cpp 

# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/edgemerger.cpp
LOADER=loader/loader.cpp mapping/grammarChecker.cpp
DATASTRUCTS=datastructures/vertex.cpp datastructures/computationset.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp datastructures/partition.cpp
TEST=../test/timer.cpp


##### build rules #####
all: comp

# prepessing
#prep: $(PREPROC)
#	$(CC) $(PREPROC) -o ../bin/prep

# edge computation program
comp: $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(TEST)
	$(CC) -ggdb $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(TEST) -o ../bin/comp

