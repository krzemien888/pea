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
			
		m_population = trimPopulation(newPopulation);

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

void GeneticAlgorithm::setPopulationLimit(const int newPopulationLimit)
{
	m_populationLimit = newPopulationLimit;
}

int GeneticAlgorithm::getPopulationLimit() const
{
	return m_populationLimit;
}

void GeneticAlgorithm::setGenerationLimit(const int newGenerationLimit)
{
	m_generationLimit = newGenerationLimit;
}

int GeneticAlgorithm::getGenerationLimit() const
{
	return m_generationLimit;
}

void GeneticAlgorithm::setGenerationsWithoutImprovementLimit(const int newLimit)
{
	m_generationsWithoutImprovementLimit = newLimit;
}

int GeneticAlgorithm::getGenerationswithoutImprovementLimit() const
{
	return m_generationsWithoutImprovementLimit;
}

void GeneticAlgorithm::setCrossoverType(const CrossoverType & selectedType)
{
	m_crossoverType = selectedType;
}

CrossoverType GeneticAlgorithm::getCrossoverType() const
{
	return m_crossoverType;
}

bool GeneticAlgorithm::verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount)
{
	return generationCount < m_generationLimit && generationWithoutImprovementCount < m_generationsWithoutImprovementLimit;
}

bool Individual::operator>(const Individual & other) const
{
	return cost > other.cost;
}

void Individual::setGenotype(std::vector<int> newGenotype, matrixGraph * graph)
{
	genotype = newGenotype;
	cost = 0;

	for (int index = 0; index < genotype.size() - 1; index++)
		cost += graph->getConnectionValue(genotype[index], genotype[index + 1]);

	cost += graph->getConnectionValue(genotype[genotype.size() - 1], genotype[0]);
}
