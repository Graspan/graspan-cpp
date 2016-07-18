#include "loader.h"

bool Loader::loadPartition(int id, Partition &p, bool readable)
{
	static char s[32 + 1] = { '0', };
	vector<Vertex>& data=p.getData();
	FILE *fp;
	char label;
	int size = 0;
	int src, degree, dst;
	int numVertices = 0;
	int i = 0;
	string str;
	if (readable) {
		cout << HUMA << endl;
		str = GRAP + "." + PART + "." + HUMA + "." + std::to_string((long long)id);
		fp = fopen(str.c_str(), "r");
	}
	else {
		cout << BINA << endl;
		str = GRAP + "." + PART + "." + BINA + "." + std::to_string((long long)id);
		fp = fopen(str.c_str(), "rb");
	}
	cout << str << endl;

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
	cout << id << " " << size << " " << numVertices << endl;
	p.setID(id);
	p.setNumEdges(size);
	p.setNumVertices(numVertices);
	fclose(fp);
	return 0;
}
