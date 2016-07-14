#include "vit.h"

//Constructor
VIT::VIT(vector<pair<int, int>> vit) { this->vit = vit; }

//Getters
vector<pair<int, int>> VIT::getVIT() { return vit; }
int VIT::getStart(int id) { return vit[id].first; }
int VIT::getEnd(int id) { return vit[id].second; }

//Setters
void VIT::setVIT(vector<pair<int, int>> vit) { this->vit = vit; }

bool VIT::is_in_partition(vertexid_t vid, partitionid_t pid)
{
	if (vid >= vit[pid].first || vid <= vit[pid].second)
		return true;
	else
		return false;
}

int VIT::partition(vertexid_t vid)
{
	for (int i = 0; i < vit.size(); i++) {
		if (vid >= vit[i].first | vid <= vit[i].second)
			return i;
	}
	return 0;
}

void VIT::writeToFile(VIT & vit)
{
	FILE *fp;
	string str;
	str = GRAP + ".vit";

	fp = fopen(str.c_str(), "w");
	for (int i = 0; i < vit.vit.size(); i++) {
		fprintf(fp, "%d\t%d\t%d\n", i, vit.vit[i].first, vit.vit[i].second);
	}	
	fclose;
}

VIT VIT::loadFromFile(char * filename)
{
	return VIT();
}
