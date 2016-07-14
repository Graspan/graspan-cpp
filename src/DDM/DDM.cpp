#include "DDM.h"

DDM::DDM(string dirName){
	//count partition file
	numPartition=0;
	struct dirent **filelist;

	int ret=scandir(dirName.c_str(),&filelist,0,alphasort);
	if(ret < 0){
		perror("scandir");
		return;
	}
	for(int i=0; i<ret; i++){
		struct dirent *file;
		file = filelist[i];
		if(file->d_name[0] != '.'){
			partitionName.push_back(file->d_name);
			numPartition++;
		}
		free(file);
	}
	free(filelist);
	originNumPartition = numPartition;

	//make partitionRate
	partitionRate.assign(numPartition,vector<double>(numPartition,0));
	edgeCnt.assign(numPartition,vector<double>(numPartition,0));
	partitionSize.assign(numPartition,0);
	
	for(int i=0;i<numPartition;i++){	
		if(f_read(dirName + partitionName.at(i))==-1){
			cout<< "can't open" <<endl;
			return;
		}
	}

	set();
}

DDM::~DDM(){}

int DDM::f_read(string name){
	std::ifstream fin;
	char str[512];
	char *p;
	int src;	

	fin.open(name);
	if(!fin) return -1;

	while(!fin.getline(str,sizeof(str)).eof()){
		vector<int> val;
		p = strtok(str," ");
		while(p != NULL){
			val.push_back(atoi(p));
			p = strtok(NULL," ");
		}
		prepare(val);
		src=val[0];
	}
	fin.close();
	return findPart(src);
}

void DDM::prepare(vector<int> val){
	int dst;
	int src = findPart(val.at(0));
	
	partitionSize[src] += val.at(1); //adding degree

	for(int i=3;i<val.size();i+=2){
		dst=findPart(val.at(i));
		edgeCnt[src][dst]++;
	}	
}

int DDM::findPart(int num){
	std::vector<int> VIT; //just test It will be fixed that real VIT
	VIT.push_back(3);
	VIT.push_back(5);
	VIT.push_back(7);

	for(int i=0;i<VIT.size();i++)
		if(num <= VIT[i])	return i;
	return -1;
}

void DDM::set(){
	for(int i=0;i<partitionRate.size();i++){
		for(int j=0;j<partitionRate[i].size();j++){
			partitionRate[i][j] = edgeCnt[i][j]/partitionSize[i];
		}
	}
}

long DDM::nextPartitionPart(){
	double max=0;
	long store_part;	//store partition

	for(int i=0;i<partitionRate.size();i++){
		for(int j=0;j<partitionRate[i].size();j++){
			if(max<partitionRate[i][j]){
				max=partitionRate[i][j];
				store_part = i << 32 | j;
			}
		}
	}
	return store_part;
}

void DDM::addPartition(string fileName){
	numPartition++;
	partitionRate.resize(numPartition,vector<double>(originNumPartition,0));
	edgeCnt.resize(numPartition,vector<double>(originNumPartition,0));
	partitionSize.resize(numPartition,0);

	int src;	
	if((src=f_read(fileName))==-1){
		cout<< "can't open" <<endl;
		return;
	}
		
	//set
	for(int i=0;i<originNumPartition;i++)
		partitionRate[src][i] = edgeCnt[src][i] / partitionSize[src];
}

void DDM::testPrint(){
	for(int i=0;i<partitionRate.size();i++){
		for(int j=0; j<partitionRate[i].size(); j++){
			cout.precision(2);
			cout << partitionRate[i][j] << "% ";
		}
		cout << endl;
	}
	long next = nextPartitionPart();
	cout << "next partition are \'" << (int)(next >> 32) << "\' and \'" << (int)next << "\'." << endl;
}
