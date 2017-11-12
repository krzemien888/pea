#include "stdafx.h"
#include "BruteforceAlgorithm.h"


Result BruteforceAlgorithm::apply(matrixGraph * graph)
{
	std::vector<int> currPermutation(graph->getSize()); 
	std::iota(std::begin(currPermutation), std::end(currPermutation), 0);
	std::vector<int>  bestPermutation = currPermutation;

	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	std::vector<int> dbgV = { 0,1,3,2 };

	startTime = std::chrono::high_resolution_clock::now();
	while (std::next_permutation(currPermutation.begin(), currPermutation.end()))
	{
		if (currPermutation == dbgV)
			;


		if (isBetter(bestPermutation, currPermutation, graph))
			bestPermutation = currPermutation;
	}
	endTime = std::chrono::high_resolution_clock::now();
	Result output;

	output.fileName = graph->getName();
	output.path = bestPermutation;
	output.result = calculateCost(bestPermutation, graph);
	output.time = (int)std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

	return output;
}

bool BruteforceAlgorithm::isBetter(std::vector<int>& best, std::vector<int>& curr, matrixGraph * graph)
{
	if (best.size() != curr.size())
		throw std::invalid_argument("BruteforceAlgorithm::isBetter: Not equal vectors given");

	return calculateCost(best, graph) > calculateCost(curr, graph);
}

long int BruteforceAlgorithm::calculateCost(std::vector<int>& permutation, matrixGraph * graph)
{
	long int result = 0;
	for (size_t i = 0; i < permutation.size(); i++)
		result += graph->getConnectionValue(permutation[i],
			(i+1 != permutation.size()) ? permutation[i + 1] : permutation[0]);

	return result;
}
