#include "preproc.h"

bool compareV(const pair<int, string> &lhs, const pair<int, string> &rhs);

Preproc::Preproc(string fileName, Context &context) {
	clock_t begin, end;
	vitSize = context.getNumPartitions();
	FILE *fp;
	char buf[512];
	char *p_token = NULL;
	char *text = NULL;
	int src, dst;
	dataSize = 0;
	count = 0;
	begin = clock();

	//fisrt file scan for count how many src is in the file
	//for malloc
	fp = fopen(fileName.c_str(), "r");
	if (fp != NULL) {
		while (NULL != fgets(buf, sizeof(buf), fp)) {
			p_token = strtok_r(buf, "\n", &text);
			p_token = strtok_r(buf, "\t", &text);
			src = atoi(p_token);
			if (src > dataSize)
				dataSize = src;
		}
		fclose(fp);
		end = clock();
		begin = clock();
		data = new vector<pair<int, string>>[dataSize + 1];
		end = clock();
	}
	else {
		assert(false, "Cannot open file ");
	}
}

void Preproc::makeVIT(string fileName, Context &context) {
	clock_t begin, end;
	int src, dst, degree;
	unsigned long long int mSize = 0;
	int size, numVertex = 0;
	string label;
	char buf[512];
	char ctemp[10];
	int i = 0, j = 0;
	int startS = -1, endS = 0;
	char *p_token = NULL;
	char *text = NULL;
	int sum = 0, cSum = 0, temp = 0;
	FILE *fp;
	set<string>::iterator it_e; //for eRules
	vector<pair<vertexid_t, vertexid_t>> &tempVIT = context.vit.getVIT();
	vector<int> &vitDegree = context.vit.getDegree();

	fp = fopen(fileName.c_str(), "r");
	if (fp != NULL) {
		//read file and save on the memory
		if (fp != NULL) {
			while (fscanf(fp, "%d\t%d\t%s\n", &src, &dst, ctemp) != EOF) {
				label += ctemp;
				data[src].push_back(std::make_pair(dst, label));
				label = "";
			}
			fclose(fp);
		}
		else {
			assert(false, "cannot open vit_file");
		}

		//add edges according to E-rules and count srcs.
		for (i = 0; i <= dataSize; i++) {
			if (data[i].size() == 0)
				continue;
			if (startS == -1)
				startS = i;
			for (it_e = eRules.begin(); it_e != eRules.end(); it_e++) {
				label = *it_e;
				data[i].push_back(std::make_pair(i, label));
			}
			std::sort(data[i].begin(), data[i].end(), compareV);
			data[i].erase(unique(data[i].begin(), data[i].end()), data[i].end());
			numVertex++;
		}
		for (i = 0; i <= dataSize; i++)
			count += data[i].size();

		//calculate mSize following the bytes.
		mSize = numVertex * 8 + count * 5;
		vitSize = 0;
		startS = -1;
		size = context.getNumPartitions();

		cout << "size =" << size << endl;
		if (mSize / (unsigned long long int)size > context.getMemBudget() / (unsigned long long int)4) {
			size = mSize / (context.getMemBudget() / (unsigned long long int) 4);
			size++;
		}
		cout << "size =" << size << endl;

		//mSize is limit size per parititons.
		mSize /= (unsigned long long int)size;
		vitSize = 0;

		startS = -1;
		for (i = 0; i <= dataSize; i++) {
			if (data[i].size() == 0)
				continue;
			if (startS == -1) {
				startS = i;
				endS = i;
			}
			sum += data[i].size() * 5;
			sum += 8;
			//if size is last one then we put data over the limit
			//because it exceeds just around 1kb.
			if (sum > mSize && vitSize != size - 1) {
				vitDegree.push_back(0);
				if (i == dataSize)
					endS = i;
				tempVIT.push_back(std::make_pair(startS, endS));
				startS = -1;
				sum = 0;
				vitSize++;
				if (i != dataSize)
					i--;

			}
			endS = i;
		}
		if (sum != 0) {
			tempVIT.push_back(std::make_pair(startS, endS));
			vitDegree.push_back(0);
			vitSize++;
		}
		context.setNumPartitions(vitSize);
		context.vit.setDegree(vitSize);


		sum = 0;
		j = 0;
		int mSum = 0;

		//this is for remember the each size of partition for get DDM.
		for (i = 0; i <= dataSize; i++) {
			if (data[i].size() == 0)
				continue;
			sum += data[i].size();
			mSum += data[i].size() * 5;
			mSum += 8;
			if (mSum > mSize && j != size - 1) {
				if (i != dataSize)
					sum -= data[i].size();
				vitDegree[j++] = sum;
				sum = 0;
				mSum = 0;
				if (i != dataSize)
					i--;
			}
		}
		if (sum != 0) {
			vitDegree[j] = sum;
		}
		//make vit file
		context.vit.writeToFile(context.getGraphFile() + ".vit");
	}
	else {
		assert(false, "Cannot open file ");
	}
}

void Preproc::makePart(Context &context) {
	vector<vector<double> > &ddmMap = context.ddm.getDdmMap();
	vector<string>::iterator it_m;
	FILE *f;
	string str;
	string name;
	int start = 0;

	//make partition files
	for (int i = 0; i < vitSize; i++) {
		str = std::to_string((long long)i);
		name = context.getGraphFile() + "." + PART + "." + HUMA + "." + str.c_str();

		f = fopen(name.c_str(), "a");
		if (f != NULL) {
			for (int j = start; j <= context.vit.getEnd(i); j++) {
				if (data[j].size() != 0) {
					fprintf(f, "%d\t%d\t", j, data[j].size());
					for (int k = 0; k < data[j].size(); k++) {
						for (int l = 1; l < mapInfo.size(); l++) {
							if (strcmp(data[j][k].second.c_str(), mapInfo[l].c_str()) == 0) {
								fprintf(f, "%d\t%d\t", data[j][k].first, l);
								break;
							}
						}
						if (i != context.vit.partition(data[j][k].first) && context.vit.partition(data[j][k].first) != -1) {
							ddmMap[i][context.vit.partition(data[j][k].first)] ++;
						}


					}
					fprintf(f, "\n");
				}
			}
			fclose(f);
			start = context.vit.getEnd(i) + 1;
		}
		else {
			assert(false, "Cannot make human file ");
		}
	}

	for (int i = 0; i < ddmMap[0].size(); i++) {
		for (int j = 0; j < ddmMap[0].size(); j++) {
			ddmMap[i][j] /= (double)context.vit.getDegree(i);
		}
	}
}

void Preproc::makeBinaryPart(Context &context) {
	FILE *f;
	string str;
	string name;
	int start = 0;
	int degree, dst;
	char label;
	//make partition files in binary files
	for (int i = 0; i < vitSize; i++) {
		str = std::to_string((long long)i);
		name = context.getGraphFile() + "." + PART + "." + BINA + "." + str.c_str();

		f = fopen(name.c_str(), "ab");
		if (f != NULL) {
			for (int j = start; j <= context.vit.getEnd(i); j++) {
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
								continue;
							}
						}
					}
				}
			}
			fclose(f);
			start = context.vit.getEnd(i) + 1;
		}
		else {
			assert(false, "Cannot make Binary file ");
		}
	}
}


void Preproc::setMapInfo(vector<string> mapInfo, set<char> eRules)
{
	set<char>::iterator it_e; //for eRules
	this->mapInfo.assign(mapInfo.begin(), mapInfo.end());

	for (it_e = eRules.begin(); it_e != eRules.end(); it_e++)
		this->eRules.insert(mapInfo[(int)*it_e]);
}



int Preproc::getNumOfPartitions()
{
	return vitSize;
}

Preproc::~Preproc()
{
	for (int i = 0; i <= dataSize; i++)
		data[i].clear();
	delete[]data;
}

bool compareV(const pair<int, string> &lhs, const pair<int, string> &rhs)
{
	if (lhs.first == rhs.first)
		return lhs.second < rhs.second;
	return lhs.first < rhs.first;
}
