#include "Preproc.h"

bool compareV(const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs);

Preproc::Preproc(char *fileName, int size) {
	clock_t begin, end;
	vitSize = size;
	part = "part";
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
	fopen_s(&fp, fileName, "r");
	while (NULL != fgets(buf, sizeof(buf), fp)) {
		p_token = strtok_s(buf, "\n", &context);
		p_token = strtok_s(buf, "\t", &context);
		src = atoi(p_token);

		if (src > dataSize)
			dataSize = src;
		count++;
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
	std::string label;
	char buf[512];
	char *ctemp[3];
	int i = 0, j = 0;
	char *p_token = NULL;
	char *context = NULL;
	int sum = 0;
	FILE *fp;

	//second file scan for get the data and put in the 
	//data (vector of array) it takes 275s need to fix for improve the time complexity
	begin = clock();
	fopen_s(&fp, fileName, "r");
	while (NULL != fgets(buf, sizeof(buf), fp)) {
		p_token = strtok_s(buf, "\n", &context);
		p_token = strtok_s(buf, "\t", &context);
		while (p_token != NULL) {
			ctemp[i++] = p_token;
			p_token = strtok_s(NULL, "\t", &context);
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
		std::sort(data[i].begin(), data[i].end(), compareV);
		data[i].erase(unique(data[i].begin(), data[i].end()), data[i].end());
		sum += data[i].size();
		if (sum >= count / vitSize + 1) {
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
	FILE *f;
	std::string str;
	std::string name;
	int start = 0;

	//make partition files, it takes 64s
	for (int i = 0; i < vitSize; i++) {
		str = std::to_string(i);
		name = this->part;
		name += str.c_str();

		fopen_s(&f, name.c_str(), "a");
		for (int j = start; j <= vertInterTable[i]; j++) {
			if (data[j].size() != 0) {
				fprintf(f, "%d\t%d\t", j, data[j].size());
				for (int k = 0; k < data[j].size(); k++)
					fprintf(f, "%d\t%s\t", data[j][k].first, data[j][k].second.c_str());
				fprintf(f, "\n");
			}
		}
		fclose(f);
		start = vertInterTable[i];
	}
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