#include "partition.h"
#include "../loader/loader.h"

//Constructor
Partition::Partition(int id, int numVertices, int numEdges, vector<Vertex> data)
{
	this->id = id;
	this->numVertices = numVertices;
	this->numEdges = numEdges;
	this->data = data;
	this->exist = true;
}

// Getters
int Partition::getID() { return id; }
int Partition::getNumVertices()
{
	return numVertices;
}
int Partition::getNumEdges()
{
	return numEdges;
}
vector<Vertex> &Partition::getData() { return data; }

bool Partition::getExist()
{
	return exist;
}

// Setters
void Partition::setID(int id) { this->id = id; }
void Partition::setNumVertices(int numVertices)
{
	this->numVertices = numVertices;
}
void Partition::setNumEdges(int numEdges)
{
	this->numEdges = numEdges;
}
void Partition::setData(vector<Vertex> data) { this->data = data; }

void Partition::setExist(bool exist)
{
	this->exist = exist;
}

void Partition::writeToFile(Partition & part, bool readable)
{
	if (!part.exist)
		return;
	//cout << part.getID() << endl;
	//cout << "write partition file" << endl;
	//cout << part.id << endl;
	FILE *fp;
	string str;
	int src, degree, dst;
	char label;
	//cout << readable << endl;
	if (readable) {
		//cout << HUMA << endl;
		str = GRAP + "." + PART + "." + HUMA + "." + std::to_string((long long)part.id);
		fp = fopen(str.c_str(), "w");
		//fprintf(fp, "%d\t%d\t%d\n", part.id, part.numVertices, part.numEdges);
		for (int i = 0; i < part.data.size(); i++) {
			//cout << part.data[i].getVertexID() << " " << part.data[i].getNumOutEdges() << endl;
			fprintf(fp, "%d\t%d\t", part.data[i].getVertexID(), part.data[i].getNumOutEdges());
			for (int j = 0; j < part.data[i].getNumOutEdges(); j++)
				fprintf(fp, "%d\t%d\t", part.data[i].getOutEdge(j), part.data[i].getOutEdgeValue(j));
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	else {
		//cout << BINA << endl;
		str = GRAP + "." + PART + "." + BINA + "." + std::to_string((long long)part.id);
		fp = fopen(str.c_str(), "wb");

		for (int i = 0; i < part.data.size(); i++) {
			src = part.data[i].getVertexID();
			degree = part.data[i].getNumOutEdges();

			fwrite((const void*) & src, sizeof(int), 1, fp);
			fwrite((const void*) & degree, sizeof(int), 1, fp);
			for (int j = 0; j < part.data[i].getNumOutEdges(); j++) {
				dst = part.data[i].getOutEdge(j);
				label = part.data[i].getOutEdgeValue(j);
				fwrite((const void*) & dst, sizeof(int), 1, fp);
				fwrite((const void*) & label, sizeof(char), 1, fp);
			}
		}
		fclose(fp);
	}
}


void Partition::loadFromFile(int id, Partition &part, bool readable)
{
	Loader::loadPartition(id, part, readable);
}

string Partition::toString()
{
	std::stringstream output;

	output << endl << "Partition id : " << id << "  Vertices : " << numVertices << "  Edges : " << numEdges << endl;

	for (int i = 0; i < numVertices; i++)
		output << data[i].toString();

	return output.str();
}
void Partition::calc_ddr(Context &context)	{
	if (!exist)
		return;
	vector<vector<double> > &ddmMap = context.ddm.getDdmMap();
	vector<double> tempDdm;
	//cout << "ddmMap[id].size " << ddmMap[id].size() << endl;
	tempDdm.resize(ddmMap[id].size(), 0);

	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].getNumOutEdges(); j++) {
			if (id != context.vit.partition(data[i].getOutEdge(j)))
				tempDdm[context.vit.partition(data[i].getOutEdge(j))] += 1 / (double)numEdges;
		}
	}
	for (int i = 0; i < tempDdm.size(); i++) {
		//cout << "id = " << id << " value = " << tempDdm[i] << endl;
		ddmMap[id][i] = tempDdm[i];
	}
}
/*
void Partition::calc_ddr(Context& context, vector<double>& ddm_entry) {
	
	VIT vit = context.vit;

	ddm_entry.clear();


	for (int i = 0; i < numVertices; ++i) {
		ddm_entry[vit.partition(data[i].getVertexID())] += 1;
	}

	for (int i = 0; i < ddm_entry.size(); ++i) {
		ddm_entry[i] /= numEdges;
	}
		
}*/
