#include "context.h"

Context::Context(int argc, char** argv) {
	//if user don't typing input value
	if(argc==1){
		//50MB
		//parameters.insert(std::make_pair(MEM_BUDGET_KEY, 7730941133));
		memBudget = (unsigned long long int) 7730941133;
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, 10));
		//src, numEdge = 8bytes dst, label = 5bytes
		//worst case is use 13bytes per edges
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, parameters[MEM_BUDGET_KEY] / 13));
		cout << "Max_Edges_Partition =" << (parameters[MEM_BUDGET_KEY]) / 13 << endl;
		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	} else{
		string compare[5] = { MEM_BUDGET_KEY , NUM_PARTITION_KEY , INSERT_SORT_FLAG ,ALTER_SCHEDULE_FLAG };
		char *p_token = NULL;
		char *context = NULL;

		for(int i=0;i<argc;i++){
			p_token = strtok_r(argv[i], "=", &context);
			if(i<2){
				parameters.insert(std::make_pair(compare[i], atoi(context)));
				if(i==0){
					parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY,parameters[compare[i]] / 13));
					cout << "Max_Edges_Partition =" << (parameters[MEM_BUDGET_KEY]) / 13 << endl;
				}
			} else{
				if((bool)context){
					flags.insert(std::make_pair(compare[i],true));
				} else{
					flags.insert(std::make_pair(compare[i],false));
				}
			}
		}
	}
}

unsigned long long int Context::getMemBudget() {
	return memBudget;
}

int Context::getNumPartitions() {
	return parameters[NUM_PARTITION_KEY];
}

int Context::getMaxEdges() {
	return parameters[MAX_EDGES_PER_PARTITION_KEY];
}

bool Context::getInsertFlag() {
	return flags[INSERT_SORT_FLAG];
}

bool Context::getAlterScheduleFlag() {
	return flags[ALTER_SCHEDULE_FLAG];
}

//void Context::setMemBudget(int memBudget) {
	//parameters[MEM_BUDGET_KEY] = memBudget;
//}
void Context::setNumPartitions(int numPartitions) {
	parameters[NUM_PARTITION_KEY] = numPartitions;
}
void Context::setMaxEdges(int maxEdges) {
	parameters[MAX_EDGES_PER_PARTITION_KEY] = maxEdges;
}

void Context::setInsertFlag(bool flag) {
	flags[INSERT_SORT_FLAG] = flag;
}
void Context::setAlterScheduleFlag(bool flag) {
	flags[ALTER_SCHEDULE_FLAG] = flag;
}
