#include "loader.h"

Partition Loader::loadBinary(char * fileName, int id)
{
	string str = fileName + std::to_string((long long)id);
	static char s[32 + 1] = { '0', };
	vector<Vertex> data;
	FILE *fp;
	char label;
	int size = 0;
	int src, degree, dst;
	int numVertices = 0;
	int i = 0;

	fp = fopen(str.c_str(), "rb");
	while (NULL != fread(&src, 4, 1, fp)) {
		vector<int> outEdges;
		vector<char> outEdgeValues;
		fread(&degree, 4, 1, fp);
		size += degree;
		numVertices++;
		cout << src << " " << degree << " ";
		for (int i = 0; i < degree; i++) {
			fread(&dst, 4, 1, fp);

			fread(&label, 1, 1, fp);

			cout << dst << " " << (int)label << " ";
			outEdges.push_back(dst);
			outEdgeValues.push_back(label);
		}
		Vertex v(0, src, outEdges, outEdgeValues);
		data.push_back(v);
	
		cout << std::endl;
	}
	return Partition(id, numVertices, size, data);
}
 /*
static Partition loadPartition(int id, bool readable = false) {} {
	
	string str = PART += BINA +=
	static char s[32 + 1] = { '0', };
	vector<Vertex> data;
	FILE *fp;
	char label;
	int size = 0;
	int src, degree, dst;
	int i = 0;

	fp = fopen(str.c_str(), "rb");
	while (NULL != fread(&src, 4, 1, fp)) {
		vector<int> outEdges;
		vector<char> outEdgeValues;
		fread(&degree, 4, 1, fp);
		size += degree;
		cout << src << " " << degree << " ";
		for (int i = 0; i < degree; i++) {
			fread(&dst, 4, 1, fp);

			fread(&label, 1, 1, fp);

			cout << dst << " " << (int)label << " ";
			outEdges.push_back(dst);
			outEdgeValues.push_back(label);
		}
		Vertex v(0, src, outEdges, outEdgeValues);
		data.push_back(v);
		cout << std::endl;
	}
	return Partition(id, size, data);
}
*/