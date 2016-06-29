#include "Preproc.h"

bool compareV(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs);

Preproc::Preproc()	{
	part = "part";
}

void Preproc::makeVIT(char *fileName, int size)	{
	std::ifstream inFile(fileName);
	std::map<int, int>::iterator it;
	std::map<int, int>::reverse_iterator it2;

	int src, dst, degree;
	std::string label;

	//use map to make VIT
	while (!inFile.eof()) {
		inFile >> src >> dst >> label;
		vitMap[src] = vitMap[src]+1;
	}
	//maximum VIT size is vitMap's size
	vertInterTable = new int[vitMap.size()];

	int i = 0;
	int sum = 0;
	//print for check
	//for (it = vitMap.begin(); it != vitMap.end(); it++) {
	//	std::cout << it->first << " " << it->second << std::endl;
	//}

	//make VIT
	it2 = vitMap.rbegin();
	for (it = vitMap.begin(); it != vitMap.end(); it++) {
		sum += it->second;
		if (sum >= size) {
			vertInterTable[i++] = it->first;
			sum = 0;
			continue;
			//print for check
			//std::cout << i << " " << vertInterTable[i - 1] << std::endl;
		}
		if (it->first == it2->first) {
			vertInterTable[i++] = it->first;
		}
	}
	this->vitSize = i;
}

void Preproc::makePart(char *fileName)	{
	std::ifstream inFile(fileName);
	int src, dst, degree;
	std::string label;
	while (!inFile.eof()) {
		int i = 0;
		inFile >> src >> dst >> label;

		//just make partition it isn't sorted
		//1 3 1
		//2 4 5
		//1 2 6 can exist
		for (int i = 0; i < (int)vitMap.size(); i++) {
			if (src <= vertInterTable[i]) {
				std::string str = std::to_string(i);
				if (std::ifstream(this->part + str))	//if file exist write std::endl;
				{
					std::ofstream outFile(this->part + str, std::ios::app);
					outFile << std::endl;
					outFile << src << " " << dst << " " << label;
				}
				else {
					std::ofstream outFile(this->part + str);
					outFile << src << " " << dst << " " << label;
				}
				break;
			}
		}
	}
}

void Preproc::partSort()	{
	outfileName = "spart";
	for (int i = 0; i < this->vitSize; i++) {
		std::string str = std::to_string(i);
		std::ifstream inFile(this->part + str);

		int src, dst, degree;
		std::string label;
		std::map<int, std::vector<std::pair<int, std::string>>> partMap;
		std::map<int, std::vector<std::pair<int, std::string>>>::iterator it;
		//read partition files
		while (!inFile.eof()) {
			inFile >> src >> dst >> label;

			partMap.insert(std::pair<int, std::vector<std::pair<int, std::string>>>(src, std::vector<std::pair<int, std::string>>()));
			partMap[src].push_back(std::make_pair(dst, label));
		}
		//sort and make outputFIle
		for (it = partMap.begin(); it != partMap.end(); it++) {
			std::sort(partMap[it->first].begin(), partMap[it->first].end(), compareV);
			std::ofstream outFile(this->outfileName + str, std::ios::app);
			if (it != partMap.begin())
				outFile << "\n";
			outFile << it->first << " " << partMap[it->first].size() << " ";
			for (int j = 0; j < (int)partMap[it->first].size(); j++) {
				outFile << partMap[it->first][j].first << " " << partMap[it->first][j].second;
				if (j != partMap[it->first].size() - 1)
					outFile << " ";
			}
		}
		partMap.clear();
	}
}


Preproc::~Preproc()
{
	delete[]vertInterTable;
	vitMap.clear();
}

bool compareV(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs)
{
	if (lhs.first == rhs.first)
		return lhs.second < rhs.second;
	return lhs.first < rhs.first;
}