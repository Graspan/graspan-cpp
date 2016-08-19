#include "repart.h"

void Repart::repartition(Partition &p1, Partition &p2, Context &context) {
	unsigned long long int size = (p1.getNumVertices() * 8 + p1.getNumEdges() * 5);
	if (size < context.getMemBudget() / (unsigned long long int) 4) {
		p2.setExist(false);
		return;
	}
	else
		size /= (unsigned long long int) 2;

	int sum = 0, check = 0;

	int i = 0;
	int end = 0;
	vector<Vertex> data;
	vector<pair<vertexid_t, vertexid_t>> &tempVIT = context.vit.getVIT();
	vector<Vertex> &dataTemp = p1.getData();

	check += dataTemp[0].getNumOutEdges() * 5;
	check += 8;
	for (i ; i < p1.getNumVertices() - 1; i++) {
		sum += dataTemp[i].getNumOutEdges();
		check += dataTemp[i + 1].getNumOutEdges() * 5;
		check += 8;
		if (check > size) {
			break;
		}
	}
	if (check <=size | p1.getNumVertices() == 1) {
		p2.setExist(false);
		return;
	}
	context.vit.setVITID(p1.getID(), context.vit.getStart(p1.getID()), dataTemp[i].getVertexID());
	i++;

	tempVIT.push_back(std::make_pair(dataTemp[i].getVertexID(), dataTemp[p1.getNumVertices() - 1].getVertexID()));

	data.resize(p1.getNumVertices() - i);
	std::copy(dataTemp.begin() + i, dataTemp.end(), data.begin());

	for (int idx = dataTemp.size()-1; idx >= i; --idx) {
		dataTemp.erase(dataTemp.begin() + idx);
	}
	dataTemp.resize(i);

	p2.setData(data);	
	p2.setID(context.getNumPartitions());
	context.setNumPartitions(context.getNumPartitions() + 1);
	p2.setNumEdges(p1.getNumEdges() - sum);
	p2.setNumVertices(p1.getNumVertices() - i);

	p1.setNumEdges(sum);
	p1.setNumVertices(i);

	context.vit.writeToFile("graph.vit");
}

void Repart::run(Partition &p1, Partition &p2, Context &context, bool newEdgesInP, bool newEdgesInQ, bool terminate) {

	Partition p12, p22;
	repartition(p1, p12, context);
	repartition(p2, p22, context);

	context.ddm.setNumPartition(context.getNumPartitions());
	context.ddm.reSize();

	if (newEdgesInP) {
		p1.calc_ddr(context);
	}
	if (newEdgesInQ) {
		p2.calc_ddr(context);
	}
	if (p12.getExist()) {
		cout << "p1 =" << p1.getID() << " p12 =" << p12.getID() << endl;
		Partition::writeToFile(p12, false, context);
		context.ddm.copy(p1.getID(), p12.getID());
		p12.calc_ddr(context);

		context.ddm.markTerminate(p1.getID(), p12.getID(), terminate, terminate);
		context.ddm.markTerminate(p2.getID(), p12.getID(), terminate, terminate);
	}
	if (p22.getExist()) {
		cout << "p2 =" << p2.getID() << " p12 =" << p22.getID() << endl;
		Partition::writeToFile(p22, false, context);
		context.ddm.copy(p2.getID(), p22.getID());

		p22.calc_ddr(context);
		context.ddm.markTerminate(p1.getID(), p22.getID(), terminate, terminate);
		context.ddm.markTerminate(p2.getID(), p22.getID(), terminate, terminate);
	}
	context.ddm.adjust(p1.getID(), p2.getID());
}
