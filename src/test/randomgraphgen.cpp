#include "randomgraphgen.h"


/**
 * given an input (the TOTAL number of vectors in the graph)
 * it returns a vector of vertices representing two "partitions" of
 * the overall graph with random grammar.
 *
 * NEEDS REDESIGN
 */
std::vector<Vertex> randGraph()
{
	std::vector<Vertex> vertices;
	srand(time(NULL));

	int numVerts;
	std::cout << "TOTAL_VERTS: ";
	std::cin >> numVerts;

	// partition sizee
	int part_size = rand() % 3 + 2;
	std::cout << part_size << std::endl;

	// ensure no overlap b/w partitions
	int p1_start = 0, p2_start = 0;
	while (!(p2_start <= p1_start - part_size || p2_start >= p1_start + part_size))
	{
		p1_start = rand() % (numVerts - part_size);
		p2_start = rand() % (numVerts - part_size);
	}

	std::cout << p1_start << ", " << p2_start << std::endl;

	// add partition 1
	std::cout << "P1:";

	for (int i = 0; i < part_size; i++)
	{
		int edges = rand() % 6;
		std::vector<int> outEdges;
		std::vector<char> outEdgeValues;

		for (int j = 0; j < edges; j++)
		{
			outEdges.push_back(rand() % numVerts);
			outEdgeValues.push_back((rand() % 4) + 97); // implicit char conversion
		}

		vertices.push_back(Vertex(i, i + p1_start, outEdges, outEdgeValues));
		std::cout << vertices[i].toString();
	}

	// add partition 2
	std::cout << "\nP2:";

	for (int i = 0; i < part_size; i++)
	{
		int edges = rand() % 5 + 1;
		std::vector<int> outEdges;
		std::vector<char> outEdgeValues;

		for (int j = 0; j < edges; j++)
		{
			outEdges.push_back(rand() % numVerts);
			outEdgeValues.push_back((rand() % 4) + 97);
		}

		vertices.push_back(Vertex(i + part_size, i + p2_start, outEdges, outEdgeValues));
		std::cout << vertices[i + part_size].toString();
	}

	return vertices;
}
