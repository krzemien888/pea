#pragma once
#include "IAlgorithm.h"
class BruteforceAlgorithm :
	public IAlgorithm
{
public:
	virtual ~BruteforceAlgorithm() = default;

	virtual Result apply(matrixGraph * graph) override;

private:
	bool isBetter(std::vector<int>& best, std::vector<int> &curr, matrixGraph* graph);
	long int calculateCost(std::vector<int> & permutation, matrixGraph* graph);
};

