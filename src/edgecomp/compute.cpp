#include "../../include/compute.h"


void getRowIndicesToMerge(ComputationSet compSets[], std::vector<LoadedVertexInterval> intervals, std::vector<int> edges, std::vector<char> vals, bool edgesEmpty, std::unordered_set<IDValuePair, Hash> newIdsToMerge, char flag)
{
	int targetRowIndex = -1;

	int newTgt = 0;
	char val = 0;

	if (!edgesEmpty)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			newTgt = edges[i];
			val = vals[i];

			for (int j = 0; j < intervals.size(); j++)
			{
				targetRowIndex = -1;
				LoadedVertexInterval interval = intervals[j];
				if (newTgt >= interval.getFirstVertex() && newTgt <= interval.getLastVertex())
				{
					targetRowIndex = newTgt - interval.getFirstVertex() + interval.getIndexStart();
					break;
				}
			}
		}
	}
}

long updateEdges(int i, ComputationSet compSets[], std::vector<LoadedVertexInterval> intervals)
{
	ComputationSet compSet = compSets[i];

	std::vector<int> oldEdges = compSet.getOldEdges();
	std::vector<char> oldVals = compSet.getOldVals();

	std::vector<int> newEdges = compSet.getNewEdges();
	std::vector<char> newVals = compSet.getNewVals();

	bool oldEdgesEmpty = (oldEdges.empty()) ? true : false;
	bool newEdgesEmpty = (newEdges.empty()) ? true : false;

	if (oldEdgesEmpty && newEdgesEmpty) return 0;

	std::unordered_set<IDValuePair, Hash> newRowIndsToMergre;
	std::unordered_set<IDValuePair, Hash> oldUnewRowIndsToMerge;

	


	return 0;
}
