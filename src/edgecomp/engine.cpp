#include <string.h>
#include "vertex.h"
#include "randomgraphgen.h"


int main(int argc, char *argv[])
{
	std::vector<Vertex> vertices;

	if (argc > 1 && strcmp(argv[1], "GEN") == 0)
		vertices = randGraph();

	

	return 0;
}
