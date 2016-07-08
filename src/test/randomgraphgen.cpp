#include "../../include/randomgraphgen.h"

/**
 * return true if edge destination already exists with the same
 * grammar
 *
 * not working 
 */
bool check_dups(std::vector<int> edges, std::vector<char> gram, int n, char c)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (n == edges[i])
			if (c == gram[i]) return true;
	}

	return false;
}


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

	int numVerts = rand() % 5 + 15;

	// partition sizee
	int part_size = rand() % 3 + 2;
//	std::cout << part_size << std::endl;

	// ensure no overlap b/w partitions
	int p1_start = 0, p2_start = 0;
	while (p1_start >= p2_start || !(p2_start <= p1_start - part_size || p2_start >= p1_start + part_size))
	{
		p1_start = rand() % (numVerts - part_size);
		p2_start = rand() % (numVerts - part_size);
	}

//	std::cout << p1_start << ", " << p2_start << std::endl;


	int ind = 0, offset = p1_start;

	for (int i = 0; i < part_size * 2; i++)
	{
		if (i == part_size) 
		{
			ind = 0;
			offset = p2_start;
		}

		int edges = rand() % 6, n, c;
		std::vector<int> outEdges;
		std::vector<char> outEdgeValues;

		for (int j = 0; j < edges; j++)
		{
			do {
				n = rand() % numVerts;
				c = rand() % 4 + 97;
			} while (check_dups(outEdges, outEdgeValues, n, c)); 
			outEdges.push_back(n);
			outEdgeValues.push_back(c); // implicit char conversion
		}
		std::sort(outEdges.begin(), outEdges.end());

		vertices.push_back(Vertex(i, ind++ + offset, outEdges, outEdgeValues));
	}

	std::cout << "P1:";
	for (int j = 0; j < vertices.size(); j++)
	{
		if (j == part_size) std::cout << std::endl << "\nP2:";

		std::cout << vertices[j].toString();
	}

	std::cout << std::endl;

	return vertices;
}
