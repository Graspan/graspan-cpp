#include "repart.h"

void Repart::repartition(Partition &p1, Partition &p2, Context &context) {
	int size = context.getMaxEdges();
	int sum = 0, check = 0;

	int i = 0;
	int end = 0;
	vector<Vertex> data;
	vector<pair<vertexid_t, vertexid_t>> &tempVIT = context.vit.getVIT();

	vector<Vertex> &dataTemp = p1.getData();
	check += dataTemp[0].getNumOutEdges();
	for (i ; i < p1.getNumVertices() - 1; i++) {
	//	cout << "getVertex = " << i << " " << dataTemp[i].getVertexID() << endl;
		sum += dataTemp[i].getNumOutEdges();
		check += dataTemp[i + 1].getNumOutEdges();
		if (check > size) {
			break;
		}
	}
	if (check <= size) {
		p2.setExist(false);
		return;
	}
	cout << "sum = " << sum << " check = " << check << " p1 first = " << context.vit.getStart(p1.getID()) << " p1 end = " << dataTemp[i].getVertexID() << endl;
	context.vit.setVITID(p1.getID(), context.vit.getStart(p1.getID()), dataTemp[i].getVertexID());
	i++;
	cout << " p2 first = " << dataTemp[i].getVertexID() << " p2 end = " << dataTemp[p1.getNumVertices() - 1].getVertexID() << endl;

	tempVIT.push_back(std::make_pair(dataTemp[i].getVertexID(), dataTemp[p1.getNumVertices() - 1].getVertexID()));

	data.resize(p1.getNumVertices() - i);
	std::copy(dataTemp.begin() + i, dataTemp.end(), data.begin());
	vector<Vertex>::iterator it_v = dataTemp.begin();

	for (int j = 0; j < i; j++) {
		it_v++;
	}
	while (it_v != dataTemp.end())
		dataTemp.erase(it_v);


	p2.setData(data);
	//cout << "test = " << context.getNumPartitions() << endl;
	
	p2.setID(context.getNumPartitions());
	context.setNumPartitions(context.getNumPartitions() + 1);
	//cout << "test = " << context.getNumPartitions() << endl;
	p2.setNumEdges(p1.getNumEdges() - sum);
	p2.setNumVertices(p1.getNumVertices() - i);

	p1.setNumEdges(sum);
	p1.setNumVertices(i);


	cout << "p1 numEdges = " << p1.getNumEdges() << " p2 numEdges = " << p2.getNumEdges() << endl << endl;
	VIT::writeToFile(context.vit);
}

void Repart::run(Partition &p1, Partition &p2, Context &context) {

	Partition p12, p22;
	repartition(p1, p12, context);
	repartition(p2, p22, context);

	context.ddm.setNumPartition(context.getNumPartitions());
	context.ddm.enlarge();

	Partition::writeToFile(p1, true);
	Partition::writeToFile(p2, true);
	Partition::writeToFile(p12, true);
	Partition::writeToFile(p22, true);


	p1.calc_ddr(context);
	p2.calc_ddr(context);
	p12.calc_ddr(context);
	p22.calc_ddr(context);

}
