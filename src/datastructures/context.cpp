#include "context.h"

Context::Context(int argc, char** argv) {
	string compare[5] = { MEM_BUDGET_KEY , NUM_PARTITION_KEY , INSERT_SORT_FLAG ,ALTER_SCHEDULE_FLAG };
	char *p_token = NULL;
	char *context = NULL;

	//50MB
	parameters.insert(std::make_pair(MEM_BUDGET_KEY, 104857600));
	parameters.insert(std::make_pair(NUM_PARTITION_KEY, 10));
	//src, numEdge = 8bytes dst, label = 5bytes
	//worst case is use 13bytes per edges
	parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, parameters[MEM_BUDGET_KEY] / 13));
	cout << "Max_Edges_Partition =" << (parameters[MEM_BUDGET_KEY]) / 13 << endl;
	flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
	flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));



	for (int i = 0; i < argc; i++) {
		for (int j = 0; j < 5; j++) {
			if (!strncmp(argv[i], compare[j].c_str(), sizeof(argv[i]))) {
				p_token = strtok_r(argv[i], "=", &context);
				if (j == 0) {
					parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(context)));
					parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, parameters[MEM_BUDGET_KEY] / 13));
				}
				else if (j == 1) {
					parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(context)));
				}
				else if (j == 2) {
					if (!strncmp(context, "true", 4))
						flags.insert(std::make_pair(INSERT_SORT_FLAG, true));
				}
				else if (j == 3) {
					if (!strncmp(context, "true", 4)) 
						flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, true));
				}
				break;
			}
		}
	}	
}

int Context::getMemBudget() {
	return parameters[MEM_BUDGET_KEY];
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

void Context::setMemBudget(int memBudget) {
	parameters[MEM_BUDGET_KEY] = memBudget;
}
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
