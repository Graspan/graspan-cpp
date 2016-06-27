#include "vertex.h"
#include <unordered_map>

// Incomplete
void computeEdges(Vertex vertices[], EdgeList edges)
{
}

int arr[5] = {0, 1, 2, 3, 4};

void concat_vectors(std::vector<int> &dst, std::vector<int> src)
{
	for (int i = 0; i < src.size(); i++)
		dst.push_back(src[i]);
}

void find_new_edges(Vertex &src, std::unordered_map<int, Vertex> graph)
{
	std::vector<int> dstVerts;

	for (int i = 0; i < src.getNumOutEdges(); i++)
	{
		dstVerts.push_back(src.getOutEdge(i));
		Vertex dst = graph.at(src.getOutEdge(i));
		concat_vectors(dstVerts, dst.getOutEdges());
	}

	src.setOutEdges(dstVerts);
}
