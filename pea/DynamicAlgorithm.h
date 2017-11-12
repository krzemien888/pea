#pragma once
#include "IAlgorithm.h"
#include "stdafx.h"


class DynamicAlgorithm final :
	public IAlgorithm
{
public:
	virtual ~DynamicAlgorithm() = default;
	virtual Result apply(matrixGraph* graph) override;
private:
	int getCost(int start, int set, matrixGraph* graph);
	void getPath(int start, int set, std::vector<int> &output);

	int getValue(int x, int y);
	int getPathValue(int x, int y);

	void setValue(int x, int y, int value);
	void setPathValue(int x, int y, int value);

	int npow;
	
	std::vector<std::vector<int>> valueVector;
	std::vector<std::vector<int>> pathVector;
};
