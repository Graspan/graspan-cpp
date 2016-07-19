#include "context.h"

Context::Context(int argc, char** argv) {
	if (argc == 1) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, 1000));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, 3));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, 10));

		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	}
	else if (argc == 2) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(argv[1])));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, 3));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, 10));

		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	}
	else if (argc == 3) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(argv[1])));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(argv[2])));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, 10));

		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	}
	else if (argc == 4) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(argv[1])));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(argv[2])));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, atoi(argv[3])));

		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	}
	else if (argc == 5) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(argv[1])));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(argv[2])));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, atoi(argv[3])));

		//flags.insert(std::make_pair(INSERT_SORT_FLAG, argv[4]));
		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
	}
	else if (argc == 6) {
		parameters.insert(std::make_pair(MEM_BUDGET_KEY, atoi(argv[1])));
		parameters.insert(std::make_pair(NUM_PARTITION_KEY, atoi(argv[2])));
		parameters.insert(std::make_pair(MAX_EDGES_PER_PARTITION_KEY, atoi(argv[3])));

		//flags.insert(std::make_pair(INSERT_SORT_FLAG, argv[4]));
		//flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, argv[5]));
		flags.insert(std::make_pair(INSERT_SORT_FLAG, false));
		flags.insert(std::make_pair(ALTER_SCHEDULE_FLAG, false));
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