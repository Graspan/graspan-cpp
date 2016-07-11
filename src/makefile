CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread


##### source files #####
# preprocessing
PREPROC=preproc/main.cpp preproc/Preproc.cpp preproc/Preproc.h

# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/grammarchecker.cpp
DATASTRUCTS=datastructures/vertex.cpp datastructures/computationset.cpp datastructures/loadedvertexinterval.cpp
TEST=test/randomgraphgen.cpp ../test/timer.cpp test/mergetest/*


##### build rules #####
all: preproc comp

# preprocessing
#preproc: $(PREPROC)
#	$(CC) $(PREPROC) -o ../bin/preproc

# edge computation program
comp: $(COMPUTATION) $(DATASTRUCTS) $(TEST)
	$(CC) $(COMPUTATION) $(DATASTRUCTS) $(TEST) -o ../bin/comp

