#include "loader.h"

void Loader::loadBinary(char * fileName)
{
	static char s[32 + 1] = { '0', };
	FILE *fp;
	char label;
	int src, degree, dst;
	int i = 0;

	fp = fopen(fileName, "rb");
	while (NULL != fread(&src, 4, 1, fp)) {
		std::vector<int> outEdges;
		std::vector<char> outEdgeValues;
		fread(&degree, 4, 1, fp);
		std::cout << src << " " << degree << " ";
		for (int i = 0; i < degree; i++) {
			fread(&dst, 4, 1, fp);

			fread(&label, 1, 1, fp);

			std::cout << dst << " " << (int)label << " ";
			outEdges.push_back(dst);
			outEdgeValues.push_back(label);
		}
		Vertex v(0, src, outEdges, outEdgeValues);
		testt.push_back(v);
		std::cout << std::endl;

	}
}

std::vector<Vertex> Loader::getData()
{
	return this->testt;
}
