#include "preproc.h"

bool compareV(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs);

Preproc::Preproc(char *fileName, int size) {
	clock_t begin, end;
	vitSize = size;
	part = "part";
	bpart = "bpart";
	FILE *fp;
	char buf[512];
	char *p_token = NULL;
	char *context = NULL;
	int src;
	dataSize = 0;
	count = 0;
	begin = clock();
	//fisrt file scan for count how many src is in the file
	//for memory allocation it takes 19s
	fp = fopen(fileName, "r");
	while (NULL != fgets(buf, sizeof(buf), fp)) {
		p_token = strtok_r(buf, "\n", &context);
		p_token = strtok_r(buf, "\t", &context);
		src = atoi(p_token);

		if (src > dataSize)
			dataSize = src;
	}
	fclose(fp);
	end = clock();
	std::cout << "Preproc data count time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	//memory allocation, it takes 10s
	begin = clock();
	data = new std::vector<std::pair<int, std::string>>[dataSize + 1];
	vertInterTable = new int[dataSize + 1];
	end = clock();
	std::cout << "memory allocation time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

}

void Preproc::makeVIT(char *fileName) {
	clock_t begin, end;
	int src, dst, degree;
	int size;
	std::string label;
	char buf[512];
	char *ctemp[3];
	int i = 0, j = 0;
	char *p_token = NULL;
	char *context = NULL;
	int sum = 0;
	FILE *fp;
	std::set<std::string>::iterator it_e; //for eRules

										  //second file scan for get the data and put in the 
										  //data (vector of array) it takes 275s need to fix for improve the time complexity
	begin = clock();
	fp = fopen(fileName, "r");
	while (NULL != fgets(buf, sizeof(buf), fp)) {
		p_token = strtok_r(buf, "\n", &context);
		p_token = strtok_r(buf, "\t", &context);
		while (p_token != NULL) {
			ctemp[i++] = p_token;
			p_token = strtok_r(NULL, "\t", &context);
		}
		src = atoi(ctemp[0]);
		dst = atoi(ctemp[1]);
		label = ctemp[2];

		data[src].push_back(std::make_pair(dst, label));
		i = 0;
	}
	fclose(fp);
	end = clock();
	std::cout << "makeVIT data input time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

	//sorting the vector of array and make VIT, it takes 88s
	begin = clock();
	for (i = 0; i <= dataSize; i++) {
		if (data[i].size() == 0)
			continue;
		for (it_e = eRules.begin(); it_e != eRules.end(); it_e++) {	//add 
			label = *it_e;
			data[i].push_back(std::make_pair(i, label));
		}
		std::sort(data[i].begin(), data[i].end(), compareV);
		data[i].erase(unique(data[i].begin(), data[i].end()), data[i].end());
		count += data[i].size();
	}
	if (count % vitSize == 0)
		size = count / vitSize;
	else
		size = count / vitSize + count %vitSize;

	for (i = 0; i <= dataSize; i++) {
		sum += data[i].size();
		if (sum >= size) {
			vertInterTable[j++] = i;
			sum = 0;
		}
	}
	if (sum != 0)
		vertInterTable[j++] = i - 1;
	end = clock();
	std::cout << "makeVIT sorting time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;

}

void Preproc::makePart() {
	std::vector<std::string>::iterator it_m;
	FILE *f;
	std::string str;
	std::string name;
	int start = 0;

	//make partition files, it takes 64s
	for (int i = 0; i < vitSize; i++) {
		str = std::to_string((long long)i);
		name = this->part;
		name += str.c_str();

		f = fopen(name.c_str(), "a");

		for (int j = start; j <= vertInterTable[i]; j++) {
			if (data[j].size() != 0) {
				fprintf(f, "%d\t%d\t", j, data[j].size());
				for (int k = 0; k < data[j].size(); k++) {
					for (int l = 0; l < mapInfo.size(); l++) {
						if (strcmp(data[j][k].second.c_str(), mapInfo[l].c_str()) == 0) {
							fprintf(f, "%d\t%d\t", data[j][k].first, l);
							break;
						}
					}
				}
				fprintf(f, "\n");
			}
		}
		fclose(f);
		start = vertInterTable[i];
	}
}

void Preproc::makeBinaryPart() {
	FILE *f;
	std::string str;
	std::string name;
	int start = 0;
	int degree, dst;
	char label;
	//make partition files in binary files
	for (int i = 0; i < vitSize; i++) {
		str = std::to_string((long long)i);
		name = this->bpart;
		name += str.c_str();

		f = fopen(name.c_str(), "ab");
		for (int j = start; j <= vertInterTable[i]; j++) {
			if (data[j].size() != 0) {

				fwrite((const void*)& j, sizeof(int), 1, f);
				degree = data[j].size();
				fwrite((const void*)&degree, sizeof(int), 1, f);
				for (int k = 0; k < data[j].size(); k++) {
					for (int l = 0; l < mapInfo.size(); l++) {
						if (strcmp(data[j][k].second.c_str(), mapInfo[l].c_str()) == 0) {
							dst = data[j][k].first;
							fwrite((const void*)& dst, sizeof(int), 1, f);
							label = l;
							fwrite((const void*)& label, sizeof(char), 1, f);

						}
					}
				}
			}
		}
		fclose(f);
		start = vertInterTable[i];
	}
}


void Preproc::setMapInfo(std::vector<std::string> mapInfo, std::set<char> eRules)
{
	std::set<char>::iterator it_e; //for eRules
	this->mapInfo.assign(mapInfo.begin(), mapInfo.end());

	for (it_e = eRules.begin(); it_e != eRules.end(); it_e++)
		this->eRules.insert(mapInfo[(int)*it_e]);
}

Preproc::~Preproc()
{
	delete[]vertInterTable;
	for (int i = 0; i <= dataSize; i++)
		data[i].clear();
	delete[]data;
}

bool compareV(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs)
{
	if (lhs.first == rhs.first)
		return lhs.second < rhs.second;
	return lhs.first < rhs.first;
}
