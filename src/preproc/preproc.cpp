#include "preproc.h"

bool compareV(const pair<int, string> &lhs, const pair<int, string> &rhs);

Preproc::Preproc(string fileName, Context &context) {
	clock_t begin, end;
	vitSize = context.getNumPartitions();
	FILE *fp;
	char buf[512];
	char *p_token = NULL;
	char *text = NULL;
	int src , dst;
	dataSize = 0;
	count = 0;
	begin = clock();
	//fisrt file scan for count how many src is in the file
	//for memory allocation it takes 19s
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
		//cout << "Preproc data count time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

		//memory allocation, it takes 10s
		begin = clock();
		data = new vector<pair<int, string>>[dataSize + 1];
		dataInfo = new bool[dataSize];
		for (int i = 0; i < dataSize; i++)
			dataInfo[i] = false;
		end = clock();
		//cout << "memory allocation time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;
	}
	else {
		assert(false, "Cannot open file ");
	}
}

void Preproc::makeVIT(string fileName, Context &context) {
	clock_t begin, end;
	int src, dst, degree;
	int size, mSize, numVertex = 0;
	string label;
	char buf[512];
	char ctemp[10];
	int i = 0, j = 0;
	int startS = -1, endS = 0;
	char *p_token = NULL;
	char *text = NULL;
	int sum = 0;
	FILE *fp;
	set<string>::iterator it_e; //for eRules
	vector<pair<vertexid_t, vertexid_t>> &tempVIT = context.vit.getVIT();
	vector<int> &vitDegree = context.vit.getDegree();

										  //second file scan for get the data and put in the 
										  //data (vector of array) it takes 275s need to fix for improve the time complexity
	//begin = clock();
	fp = fopen(fileName.c_str(), "r");
	if (fp != NULL) {
		//read file and save on the memory
		if (fp != NULL) {
			while (fscanf(fp, "%d\t%d\t%s\n", &src, &dst, ctemp) != EOF) {
				label += ctemp;
				data[src].push_back(std::make_pair(dst, label));
				dataInfo[src] = true;
				label = "";
			}
			fclose(fp);
		}
		else {
			assert(false, "cannot open vit_file");
		}
		/*
		while (NULL != fgets(buf, sizeof(buf), fp)) {
			p_token = strtok_r(buf, "\n", &text);
			if (buf == NULL)
				cout << "TTTTTTTT!" << endl;
			p_token = strtok_r(buf, "\t", &text);
			while (p_token != NULL) {
				ctemp[i++] = p_token;
				p_token = strtok_r(NULL, "\t", &text);
			}
			src = atoi(ctemp[0]);
			dst = atoi(ctemp[1]);
			label = ctemp[2];

			data[src].push_back(std::make_pair(dst, label));
			//dataInfo[dst] = true;
			dataInfo[src] = true;
			i = 0;
			cout << src << " " << dst << endl;
		}
		fclose(fp);*/
		//end = clock();
		//cout << "makeVIT data input time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

		//sorting the vector of array
		//begin = clock();
		for (i = 0; i <= dataSize; i++) {
			if (data[i].size() == 0 && !dataInfo[i])
				continue;
			if (startS == -1)
				startS = i;
			for (it_e = eRules.begin(); it_e != eRules.end(); it_e++) {	//add 
				label = *it_e;
				data[i].push_back(std::make_pair(i, label));
				count++;
			}
			std::sort(data[i].begin(), data[i].end(), compareV);
			data[i].erase(unique(data[i].begin(), data[i].end()), data[i].end());
			numVertex++;
		}
		for (i = 0; i <= dataSize; i++)
			count += data[i].size();

		//make vit
		//cout << count - vitSize*(int)(count / vitSize) << endl;
		if (count - vitSize*(int)(count / vitSize) < vitSize / (float)2)
			size = count / vitSize;
		else
			size = count / vitSize + 1;

		mSize = numVertex * 8 + count * 5;
		mSize /= context.getMemBudget();
		vitSize = 0;
		//cout << "count =" << count << " size =" << size << endl;
		/*for (i = 0; i <= dataSize; i++) {
			if (startS == -1)
				startS = i;
			endS = i;
			sum += data[i].size();
			if (sum >= size) {
				//	cout << "sum =" << sum << "size =" << size << endl;
				vitDegree.push_back(0);
				tempVIT.push_back(std::make_pair(startS, endS));
				startS = -1;
				sum = 0;
				vitSize++;
			}
		}*/
		cout << "Size =" << size << ", Msize =" << mSize << endl;
		for (i = 0; i <= dataSize; i++) {
			if (data[i].size() == 0)
				continue;
			endS = i;
			sum += data[i].size() * 5;
			sum += 8;
			if (sum >= context.getMemBudget()) {
				//	cout << "sum =" << sum << "size =" << size << endl;
				vitDegree.push_back(0);
				tempVIT.push_back(std::make_pair(startS, endS));
				startS = i + 1;
				sum = 0;
				vitSize++;
			}
		}
		if (sum != 0) {
			tempVIT.push_back(std::make_pair(startS, endS));
			vitDegree.push_back(0);
			vitSize++;
		}
		cout << "NUMBER OF PARTITION =" << vitSize << endl;
		context.setNumPartitions(vitSize);
		context.vit.setDegree(vitSize);


		sum = 0;
		j = 0;
		int mSum = 0;

		p = new Partition[vitSize];

		for (i = 0; i <= dataSize; i++) {
			sum += data[i].size();
			mSum += data[i].size() * 5;
			mSum += 8;
			if (mSum >= context.getMemBudget()) {
				vitDegree[j++] = sum;
				sum = 0;
				mSum = 0;
			}
		}
		if (sum != 0) {
			vitDegree[j] = sum;
		}
		//end = clock();
		context.vit.writeToFile("graph.vit");
		//cout << "makeVIT sorting time : " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
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
		name = GRAP + "." + PART + "." + HUMA + "." + str.c_str();

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
							ddmMap[i][context.vit.partition(data[j][k].first)] += 1 / (double)context.vit.getDegree(i);
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
	
	/*
	int size = 0, numVertices = 0;
	for (int i = 0; i < vitSize; i++) {
		vector<Vertex>& pData = p[i].getData();
		pData.clear();
		vector<vertexid_t> outEdges;
		vector<label_t> outEdgeValues;

		for (int j = 0; j <= dataSize; j++) {
			if (data[j].size() == 0)
				continue;
			size += data[j].size();
			numVertices++;
			for (int k = 0; k < data[j].size(); k++) {
				outEdges.push_back(data[j][k].first);

				for (int l = 1; l < mapInfo.size(); l++) {
					if (strcmp(data[j][k].second.c_str(), mapInfo[l].c_str()) == 0) {
						outEdgeValues.push_back(l);
						break;
					}
				}
			}
			Vertex v(0, j, outEdges, outEdgeValues);
			pData.push_back(v);
		}
		p[i].setID(i);
		p[i].setNumEdges(size);
		p[i].setNumVertices(numVertices);

		cout << "Make partition " << endl;
		Partition().writeToFile(p[i], true);

		cout << "Save Partition " << i << endl;
	}*/
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
		name = GRAP + "." + PART + "." + BINA + "." + str.c_str();

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
