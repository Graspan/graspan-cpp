#include "engine.h"

#define MAX_NEW_EDGES 3000000

long totNewEdges;
long newEdgesThisIter;
int iterNo;

bool newEdgesPart1;
bool newEdgesPart2;

// FUNCTION DEFS
void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2);

void initLVIs(LoadedVertexInterval intervals[], vector<Vertex> &part1, vector<Vertex> &part2);

void computeEdges(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Context &context, unsigned long long int sizeLim);

void computeOneIteration(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Context &context);

void updatePartitions(ComputationSet compsets[], Partition &p1, Partition &p2, vector<Vertex> &part1, vector<Vertex> &part2);


/**
 * runs the edge computation for graspan
 */
int run_computation(Context &context)
{
	// load partitions into memory
	Timer loadTimer, compTimer, repartTimer;
	string str;
	string name;
	Partition p1, p2;
	partitionid_t p, q, oldP = -1, oldQ = -1;
	int roundNo = 0;
	while (context.ddm.nextPartitionPair(p, q))
	{
		cout << "##### STARTING ROUND " << ++roundNo << " #####" << endl;
		loadTimer.startTimer();
		if (p != oldP) {
			if (oldP != -1)
				Partition::writeToFile(p1, false, context);
			Loader::loadPartition(p, p1, false, context);
		}
		if (q != oldQ) {
			if (oldQ != -1)
				Partition::writeToFile(p2, false, context);
			Loader::loadPartition(q, p2, false, context);
		}
		cout << "OG NUM EDGES: " << (p1.getNumEdges() + p2.getNumEdges()) << endl;
		unsigned long long int sizeLim = (context.getMemBudget() - p1.getNumVertices() * 8 - p2.getNumVertices() * 8) / 5;
		oldP = p;
		oldQ = q;
		loadTimer.endTimer();
		cout << "P =" << p << " Q =" << q << endl;

		vector<Vertex> &part1 = p1.getData(), &part2 = p2.getData();

		ComputationSet *compsets = new ComputationSet[part1.size() + part2.size()];
		int setSize = part1.size() + part2.size();
		initCompSets(compsets, part1, part2);				// Initialize the ComputationSet list
		
		LoadedVertexInterval intervals[2] = {LoadedVertexInterval{p}, LoadedVertexInterval{q}};
		initLVIs(intervals, part1, part2);					// Initialize the Loaded Vertex Intervals

		cout << "== COMP START ==" << endl;
		compTimer.startTimer();
		computeEdges(compsets, setSize, intervals, context, sizeLim);
		compTimer.endTimer();
		cout << "== COMP END ==" << endl;

		updatePartitions(compsets, p1, p2, part1, part2);	// store information to partitions

		cout << "NEW NUM EDGES: " << (p1.getNumEdges() + p2.getNumEdges()) << endl;

		delete[] compsets;
		if (totNewEdges > 0) {
			cout << "== REPA START ==" << endl;
			repartTimer.startTimer();
			Repart::run(p1, p2, context, intervals[0].hasNewEdges(), intervals[1].hasNewEdges(), newEdgesThisIter);
			repartTimer.endTimer();


			cout << "== REPA END ==" << endl;
		}

		if (newEdgesThisIter <= 0) {
			context.ddm.markTerminate(p, q, 0, 0);
			context.ddm.adjustRow(p);
			context.ddm.adjustRow(q);
			cout << intervals[0].hasNewEdges() << endl;
			cout << intervals[1].hasNewEdges() << endl;
		}
		else {
			context.ddm.set(p, q, 1);
		}
		str = std::to_string((long long)roundNo);
		name = context.getGraphFile() + ".ddm." + str;
		context.ddm.save_DDM(name.c_str());

		cout << "===== ROUND INFO =====" << endl;
		cout << "NEW EDGES: " << totNewEdges << endl;
		cout << "LOAD TIME: " << loadTimer.hmsFormat() << endl;
		cout << "COMP TIME: " << compTimer.hmsFormat() << endl;
		cout << "REPA TIME: " << repartTimer.hmsFormat() << endl <<  endl << endl;
	}
	Partition::writeToFile(p1, false, context);
	Partition::writeToFile(p2, false, context);

	return 0;
}

/**
 * Get start and end indices of each partition
 *
 * @param vertices
 * @param compsets
 * @param intervals
 */
void computeEdges(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Context &context, unsigned long long int sizeLim)
{
	Timer iterTimer;
	iterNo = 0;
	totNewEdges = 0;

	cout << "NEW EDGES LIMIT: " << sizeLim << endl;
	
	do {
		cout << "===== STARTING ITERATION " << ++iterNo << endl;
		iterTimer.startTimer();
		computeOneIteration(compsets, setSize, intervals, context);

		totNewEdges += newEdgesThisIter;

		for (int i = 0; i < setSize; i++)
		{
			compsets[i].setOldEdges(compsets[i].getoldUnewEdges());
			compsets[i].setOldVals(compsets[i].getoldUnewVals());
			compsets[i].setoldUnewEdges(compsets[i].getoUnUdEdges());
			compsets[i].setoldUnewVals(compsets[i].getoUnUdVals());
			compsets[i].setNewEdges(compsets[i].getDeltaEdges());
			compsets[i].setNewVals(compsets[i].getDeltaVals());
		}
		iterTimer.endTimer();

		cout << "EDGES PER SECND: " << (double)newEdgesThisIter / (double)(iterTimer.totalTime() / 1000) << endl;
		cout << "EDGES THIS ITER: " << newEdgesThisIter << endl;
		cout << "NEW EDGES TOTAL: " << totNewEdges << endl;
		cout << "ITERATER  TIME   " << iterTimer.hmsFormat() << endl << endl;

		if (totNewEdges > sizeLim) break;
	} while (newEdgesThisIter > 0);
}

/**
 * compute the new edges of each vertex simultaneously
 *
 * @param vertices
 * @param compsets
 * @param intervals
 */
void computeOneIteration(ComputationSet compsets[], int setSize, LoadedVertexInterval intervals[], Context &context)
{
	newEdgesThisIter = 0;
	#pragma omp parallel for num_threads(64) reduction (+:newEdgesThisIter)
	for (int i = 0; i < setSize; i++)
	{
		long newEdges = 0;

		newEdges += updateEdges(i, compsets, intervals, context);
		if (newEdges > 0 && (i >= intervals[0].getIndexStart() && i <= intervals[0].getIndexEnd()))
			intervals[0].setNewEdgeAdded(true);
		else if (newEdges > 0 && (i >= intervals[1].getIndexStart() && i <= intervals[1].getIndexEnd()))
			intervals[1].setNewEdgeAdded(true);

		newEdgesThisIter += newEdges;
	}
}

/**
 * load both partitions into a list of ComputationSet
 *
 * @param compsets[]		-list of ComputationSet
 * @param part1				-vector of Vertex representing partition 1
 * @param part2				-vector of Vertex representing partition 2
 */
void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	for (int i = 0; i < part1.size(); i++)
	{
		compsets[i].setNewEdges(part1[i].getOutEdges());
		compsets[i].setNewVals(part1[i].getOutEdgeValues());
		compsets[i].setoldUnewEdges(part1[i].getOutEdges());
		compsets[i].setoldUnewVals(part1[i].getOutEdgeValues());
	}

	int offset = part1.size();
	for (int j = part1.size(); j < part1.size() + part2.size(); j++)
	{
		compsets[j].setNewEdges(part2[j - offset].getOutEdges());
		compsets[j].setNewVals(part2[j - offset].getOutEdgeValues());
		compsets[j].setoldUnewEdges(part2[j - offset].getOutEdges());
		compsets[j].setoldUnewVals(part2[j - offset].getOutEdgeValues());
	}
}

/**
 * initialize the LoadedVertexInterval list using the partition information
 */
void initLVIs(LoadedVertexInterval intervals[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	intervals[0].setFirstVertex(part1[0].getVertexID());
	intervals[0].setLastVertex(part1[part1.size() - 1].getVertexID());
	intervals[0].setIndexStart(0);
	intervals[0].setIndexEnd(part1.size()-1);

	intervals[1].setFirstVertex(part2[0].getVertexID());
	intervals[1].setLastVertex(part2[part2.size() - 1].getVertexID());
	intervals[1].setIndexStart(part1.size());
	intervals[1].setIndexEnd(part1.size() + part2.size()-1);
}

/**
 * save newly computed Edges back to their respective vertices
 */
void updatePartitions(ComputationSet compsets[], Partition &p1, Partition &p2, vector<Vertex> &part1, vector<Vertex> &part2)
{
	int p1Edges = 0;
	for (int i = 0; i < part1.size(); i++)
	{
		p1Edges += compsets[i].getoldUnewEdges().size();
		part1[i].setNumOutEdges(compsets[i].getoldUnewEdges().size());
		part1[i].setOutEdges(compsets[i].getoldUnewEdges());
		part1[i].setOutEdgeValues(compsets[i].getoldUnewVals());
	}

	int offset = part1.size(), p2Edges = 0;
	for (int j = 0; j < part2.size(); j++)
	{
		p2Edges += compsets[j+offset].getoldUnewEdges().size();
		part2[j].setNumOutEdges(compsets[j+offset].getoldUnewEdges().size());
		part2[j].setOutEdges(compsets[j+offset].getoldUnewEdges());
		part2[j].setOutEdgeValues(compsets[j+offset].getoldUnewVals());
	}

	p1.setNumEdges(p1Edges);
	p2.setNumEdges(p2Edges);
}
