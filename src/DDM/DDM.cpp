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

	//make partitionRate
	partitionRate.assign(numPartition,vector<double>(numPartition,0));
	edgeCnt.assign(numPartition,vector<double>(numPartition,0));
	partitionSize.assign(numPartition,0);
	
	std::ifstream fin;
	char str[512];
	char *p;
	for(int i=0;i<numPartition;i++){
		fin.open(dirName + partitionName.at(i));

		while(!fin.getline(str,sizeof(str)).eof()){
			vector<int> val;
			p = strtok(str," ");
			while(p != NULL){
				val.push_back(atoi(p));
				p = strtok(NULL," ");
			}
			prepare(val);
		}
		fin.close();
	}
	set();
}

DDM::~DDM(){}

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
	int VIT[]={3,5}; //just test It will be fixed that real VIT

	for(int i=0;i<2;i++)
		if(num <= VIT[i])	return i;
	return -1;
}

void DDM::set(){
	for(int i=0;i<numPartition;i++){
		for(int j=0;j<numPartition;j++){
			partitionRate[i][j] = edgeCnt[i][j]/partitionSize[i];
		}
	}
}

long DDM::nextPartitionPart(){return 1;}

void DDM::testPrint(){
	for(int i=0;i<numPartition;i++){
		for(int j=0; j<numPartition; j++){
			cout.precision(2);
			cout << partitionRate[i][j] << "% ";
		}
		cout << endl;
	}
}
