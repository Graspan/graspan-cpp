#include "vit.h"

//Constructor
//ALL small methods should be inlined instead!!!

//Getters
vector<pair<vertexid_t, vertexid_t>> &VIT::getVIT() { return vit; }
int VIT::getStart(int pid) { return vit[pid].first; }
int VIT::getEnd(int pid) { return vit[pid].second; }

vector<int> &VIT::getDegree()
{
	return degree;
}

int VIT::getDegree(int pid)
{
	return degree[pid];
}

int VIT::getNumVertex()
{
	return vit.size();
}

//Setters
void VIT::setVIT(vector<pair<int, int>> vit) { this->vit = vit; }

void VIT::setDegree(int numPartition)
{
	if (numPartition > degree.size())
		for (int i = 0; i < numPartition - degree.size(); i++)
			degree.push_back(0);
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
	return -1;
}

bool VIT::writeToFile(string fname)
{
	FILE *fp;
	//string str = "../resources/" + GRAP + ".vit"; // this should not be hard coded like this, when you run the system, the path is not same as us

	fp = fopen(fname.c_str(), "w");
	if (fp != NULL) {

		for (int i = 0; i < vit.size(); i++) {
			fprintf(fp, "%d\t%d\t%d\n", i, vit[i].first, vit[i].second);
		}
		fclose(fp);
	}
	else {
		assert(false, "cannot write vit_file");
		return false;
	}
	return true;
}

bool VIT::loadFromFile(string fname)
{
	FILE *fp;
//	string str = "../resources/" + GRAP + ".vit"; // this should not be hard coded like this, when you run the system, the path is not same as us
	vit.clear();
	int i,start,end;

	fp = fopen(fname.c_str(), "r");

	if (fp != NULL) { 
		while (fscanf(fp, "%d\t%d\t%d\n", &i, &start, &end) != EOF) {
			vit.push_back(std::make_pair(start, end));
		}
		fclose(fp);
	}else {
		assert(false, "cannot open vit_file");
		return false;
	}
	return true;	
}

string VIT::toString() {
  
  std::stringstream output;
  
  for (int i = 0; i < vit.size(); i++) {
    output << i << " " <<  vit[i].first << " " <<  vit[i].second <<endl;
  }
  
  return output.str();
}

