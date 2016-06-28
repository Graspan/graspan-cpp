CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread

# source files
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp
DATASTRUCTS=datastructures/vertex.cpp datastructures/computationset.cpp datastructures/loadedvertexinterval.cpp
TEST=test/randomgraphgen.cpp

## 
# Main program
##
comp: $(COMPUTATION) $(DATASTRUCTS) $(TEST)
	$(CC) $(COMPUTATION) $(DATASTRUCTS) $(TEST) -o ../bin/comp

