#pragma once
#include "TSPHeader.h"
#include  "matrixGraph.h"

class TSPHeader;
class matrixGraph;

class InstanceGenerator
{
public:

	void generate();
	virtual ~InstanceGenerator() = default;

private:

	TSPHeader getHeader(int size, bool isSymmetric);
	void writeToFile(matrixGraph &graph, TSPHeader &header);
	void getParameters(char &symmetric, int &lowBound, int &highBound);
};

