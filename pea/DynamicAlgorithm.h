#pragma once
#include "IAlgorithm.h"
#include "stdafx.h"


class DynamicAlgorithm final :
	public IAlgorithm
{
public:
	virtual ~DynamicAlgorithm() = default;
	virtual Result apply(matrixGraph* graph) override;
	virtual std::string toString() override;
private:
	int getCost(int start, long long int set, matrixGraph* graph);
	void getPath(int start, long long int set, std::vector<int> &output);

	int getValue(long long int x, long long int y);
	int getPathValue(long long int x, long long int y);

	void setValue(long long int x, long long int y, int value);
	void setPathValue(long long int x, long long int y, int value);

	long long int npow;
	
	std::vector<std::vector<int>> valueVector;
	std::vector<std::vector<int>> pathVector;
};
