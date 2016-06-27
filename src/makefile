CC=g++ -std=c++0x

# will eventually need to use threads
CFLAGS=-lpthread

EDGE_COMP=edgecomp/engine.cpp
DATASTRUCTS=datastructures/vertex.cpp 
GRAPH_GEN=test/randomgraphgen.cpp

## 
# Main program
##
comp: $(EDGE_COMP) $(DATASTRUCTS) $(GRAPH_GEN)
	$(CC) $(EDGE_COMP) $(DATASTRUCTS) $(GRAPH_GEN) -o ../bin/comp

