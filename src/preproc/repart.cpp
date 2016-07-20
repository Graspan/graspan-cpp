#include "repart.h"

void Repart::repartition(Partition &p1, Partition &p2) {
	int size = p1.getNumEdges() / 2;
	int sum = 0;
	int i = 0;
	int end = 0;
	vector<Vertex> data;
	VIT vit;
	VIT::loadFromFile(vit);
	vector<pair<vertexid_t, vertexid_t>> &tempVIT = vit.getVIT();

	vector<Vertex> &dataTemp = p1.getData();
	
	for (i ; i < p1.getNumVertices(); i++) {
		cout << "getVertex = " << i << " " << dataTemp[i].getVertexID() << endl;
		sum += dataTemp[i].getNumOutEdges();
		if (sum >= size) {
			break;
		}
	}
	cout << i << endl;
	vit.setVITID(p1.getID(), vit.getStart(p1.getID()), dataTemp[i].getVertexID());
	i++;
	tempVIT.push_back(std::make_pair(dataTemp[i].getVertexID(), dataTemp[p1.getNumVertices() - 1].getVertexID()));
	VIT::writeToFile(vit);
	data.resize(i);
	std::copy(dataTemp.begin() + i, dataTemp.end(), data.begin());
	cout << i << " " << (int)dataTemp.size() << endl;
	vector<Vertex>::iterator it_v = dataTemp.begin();

	for (int j = 0; j < i; j++) {
		it_v++;
	}
	while (it_v != dataTemp.end())
		dataTemp.erase(it_v);


	p2.setData(data);
	p2.setID(3);
	p2.setNumEdges(p1.getNumEdges() - sum);
	p2.setNumVertices(p1.getNumVertices() - i);

	p1.setNumEdges(sum);
	p1.setNumVertices(i);

}
