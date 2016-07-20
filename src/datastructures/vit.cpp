#include "vit.h"

//Constructor
VIT::VIT(vector<pair<int, int>> vit) { this->vit = vit; }

//Getters
vector<pair<vertexid_t, vertexid_t>> &VIT::getVIT() { return vit; }
int VIT::getStart(int pid) { return vit[pid].first; }
int VIT::getEnd(int pid) { return vit[pid].second; }

int *VIT::getDegree()
{
	return degree;
}

int VIT::getDegree(int pid)
{
	return degree[pid];
}

//Setters
void VIT::setVIT(vector<pair<int, int>> vit) { this->vit = vit; }

void VIT::setDegree(int numPartition)
{
	degree = new int[numPartition];
}

void VIT::setVITID(int id, vertexid_t start, vertexid_t end)
{
	vit[id].first = start;
	vit[id].second = end;
}

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
		//cout << "i " << i << " " << "vid = " << vid << " " << vit[i].first << " " << vit[i].second << endl;
		if (vid >= vit[i].first && vid <= vit[i].second)
			return i;
	}
	return 0;
}

void VIT::writeToFile(VIT & v)
{
	FILE *fp;
	string str;
	str = GRAP + ".vit";

	fp = fopen(str.c_str(), "w");
	for (int i = 0; i < v.vit.size(); i++) {
		fprintf(fp, "%d\t%d\t%d\n", i, v.vit[i].first, v.vit[i].second);
	}
	fclose(fp);
}

void VIT::loadFromFile(VIT &v)
{
	FILE *fp;
	string str;
	str = GRAP + ".vit";
	v.vit.clear();
	char buf[512];
	char *ctemp[3];
	char *p_token = NULL;
	char *context = NULL;
	int i = 0;
	fp = fopen(str.c_str(), "r");
	while (NULL != fgets(buf, sizeof(buf), fp)) {
		p_token = strtok_r(buf, "\n", &context);
		p_token = strtok_r(buf, "\t", &context);
		while (p_token != NULL) {
			ctemp[i++] = p_token;
			p_token = strtok_r(NULL, "\t", &context);
		}
		v.vit.push_back(std::make_pair(atoi(ctemp[1]), atoi(ctemp[2])));
		i = 0;
	}
	fclose(fp);
}
