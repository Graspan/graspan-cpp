#include "computationset.h"


string ComputationSet::oldString()
{
	std::stringstream output;

	vector<int> &edges = *(oldEdges);
	vector<char> &vals = *(oldVals);

	output << "= OLD ===\n";
	if (edges.empty()) output << "oldEdges empty...\n\n";
	else {
		for (int i = 0; i < edges.size(); i++)
			output << "(" << edges.at(i) << ", " << (short)vals.at(i) << ")  ";
		
		output << "\n\n";
	}

	return output.str();
}

string ComputationSet::newString()
{
	std::stringstream output;

	vector<int> &edges = *(newEdges);
	vector<char> &vals = *(newVals);

	output << "= NEW ===\n";
	if (edges.empty()) output << "newEdges empty...\n\n";
	else {
		for (int i = 0; i < edges.size(); i++)
			output << "(" << edges.at(i) << ", " << (short)vals.at(i) << ")  ";
		
		output << "\n\n";
	}

	return output.str();
}

string ComputationSet::oUnString()
{
	std::stringstream output;

	vector<int> &edges = *(oldUnewEdges);
	vector<char> &vals = *(oldUnewVals);

	output << "= OUN ===\n";
	if (edges.empty()) output << "oldUnewEdges empty...\n\n";
	else {
		for (int i = 0; i < edges.size(); i++)
			output << "(" << edges.at(i) << ", " << (short)vals.at(i) << ")  ";
		
		output << "\n\n";
	}	

	return output.str();
}

string ComputationSet::deltString()
{
	std::stringstream output;

	vector<int> &edges = *(deltaEdges);
	vector<char> &vals = *(deltaVals);

	output << "= DELT ===\n";
	if (edges.empty()) output << "deltaEdges empty...\n\n";
	else {
		for (int i = 0; i < edges.size(); i++)
			output << "(" << edges.at(i) << ", " << (short)vals.at(i) << ")  ";
		
		output << "\n\n";
	}	

	return output.str();
}

string ComputationSet::oUnUdString()
{
	std::stringstream output;

	vector<int> &edges = *(oUnUdEdges);
	vector<char> &vals = *(oUnUdVals);

	output << "= OUNUD ===\n";
	if (edges.empty()) output << "oUnUdEdges empty...\n\n";
	else {
		for (int i = 0; i < edges.size(); i++)
			output << "(" << edges.at(i) << ", " << (short)vals.at(i) << ")  ";
		
		output << "\n\n";
	}	

	return output.str();
}
