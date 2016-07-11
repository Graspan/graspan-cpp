CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread


##### source files #####
# preprocessing
PREPROC=preproc/main.cpp preproc/Preproc.cpp preproc/Preproc.h mapping/grammarChecker.cpp 

# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/grammarchecker.cpp edgecomp/edgemerger.cpp
DATASTRUCTS=datastructures/vertex.cpp datastructures/computationset.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp
TEST=../test/randomgraphgen.cpp ../test/timer.cpp


##### build rules #####
all: preproc comp

# preprocessing
#preproc: $(PREPROC)
#	$(CC) $(PREPROC) -o ../bin/preproc

# edge computation program
comp: $(COMPUTATION) $(DATASTRUCTS) $(TEST)
	$(CC) $(COMPUTATION) $(DATASTRUCTS) $(TEST) -o ../bin/comp

