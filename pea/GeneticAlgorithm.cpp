#include "stdafx.h"
#include "GeneticAlgorithm.h"


Result GeneticAlgorithm::apply(matrixGraph * graph)
{
	initPopulation();
	int generationCount = 0;
	int generationsWithoutImprovement = 0;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;


	Individual bestIndividual = m_population.getFittest();

	startTime = std::chrono::high_resolution_clock::now();
	while (verifyEndingCondition(generationCount, generationsWithoutImprovement))
	{
		auto selected = selectParents();
		auto newPopulation = crossoverPopulation(selected);
		newPopulation = mutatePopulation(newPopulation);

		m_population = newPopulation;
			
		trimPopulation();

		if (bestIndividual > m_population.getFittest())
			bestIndividual = m_population.getFittest();
	}
	endTime = std::chrono::high_resolution_clock::now();

	Result output;
	output.path = bestIndividual.genotype;
	output.result = bestIndividual.cost;
	output.time = (int)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	output.fileName = graph->getName;

	return output;
}

std::string GeneticAlgorithm::toString()
{
	return std::string();
}

bool GeneticAlgorithm::verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount)
{
	return generationCount < m_generationLimit && generationWithoutImprovementCount < m_generationsWithoutImprovementLimit;
}

bool Individual::operator>(const Individual & other) const
{
	return cost > other.cost;
}
