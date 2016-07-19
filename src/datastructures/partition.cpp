#include "partition.h"
#include "../loader/loader.h"

//Constructor
Partition::Partition(int id, int numVertices, int numEdges, vector<Vertex> data)
{
	this->id = id;
	this->numVertices = numVertices;
	this->numEdges = numEdges;
	this->data = data;
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

void Partition::writeToFile(Partition & part, bool readable)
{
	cout << "write partition file" << endl;
	
	FILE *fp;
	string str;
	if (readable) {
		cout << HUMA << endl;
		str = GRAP + "." + PART + "." + HUMA + "." + std::to_string((long long)part.id);
		fp = fopen(str.c_str(), "w");
		//fprintf(fp, "%d\t%d\t%d\n", part.id, part.numVertices, part.numEdges);
		for (int i = 0; i < part.data.size(); i++) {
			fprintf(fp, "%d\t%d\t", part.data[i].getVertexID(), part.data[i].getNumOutEdges());
			for (int j = 0; j < part.data[i].getNumOutEdges(); j++)
				fprintf(fp, "%d\t%d\t", part.data[i].getOutEdge(j), part.data[i].getOutEdgeValue(j));
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	else {
		cout << BINA << endl;
		str = GRAP + "." + PART + "." + BINA + "." + std::to_string((long long)part.id);
		fp = fopen(str.c_str(), "wb");
		fwrite((const void*)& part.id, sizeof(int), 1, fp);
		fwrite((const void*)& part.numVertices, sizeof(int), 1, fp);
		fwrite((const void*)& part.numEdges, sizeof(int), 1, fp);
		for (int i = 0; i < part.data.size(); i++) {
			fwrite((const void*)part.data[i].getVertexID(), sizeof(int), 1, fp);
			fwrite((const void*)part.data[i].getNumOutEdges(), sizeof(int), 1, fp);
			for (int j = 0; j < part.data[i].getNumOutEdges(); j++) {
				fwrite((const void*)part.data[i].getOutEdge(j), sizeof(int), 1, fp);
				fwrite((const void*)part.data[i].getOutEdgeValue(j), sizeof(int), 1, fp);
			}
		}
		fclose(fp);
	}
}


void Partition::loadFromFile(int id, Partition &part, bool readable)
{
	Loader::loadPartition(id, part, readable);
}
