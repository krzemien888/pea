#include "stdafx.h"
#include "GeneticAlgorithm.h"


Result GeneticAlgorithm::apply(matrixGraph * graph)
{
	initPopulation(graph);
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
	output.fileName = graph->getName();

	return output;
}

std::string GeneticAlgorithm::toString()
{
	std::string output;

	output.append("-");
	switch (getCrossoverType())
	{
	case CrossoverType::PMX:
		output.append("PMX");
		break;
	case CrossoverType::OX:
		output.append("OX");
		break;
	case CrossoverType::CX:
		output.append("CX");
		break;
	}
	output.append("-");
	output.append(std::to_string(getGenerationLimit()));
	output.append("-");
	output.append(std::to_string(getGenerationswithoutImprovementLimit()));
	output.append("-");
	output.append(std::to_string(getPopulationLimit()));
	return output;
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

void GeneticAlgorithm::setGraph(matrixGraph * graph)
{
	m_graph = graph;
}

void GeneticAlgorithm::setCrossoverType(const CrossoverType & selectedType)
{
	m_crossoverType = selectedType;
}

CrossoverType GeneticAlgorithm::getCrossoverType() const
{
	return m_crossoverType;
}

Population GeneticAlgorithm::trimPopulation(Population & populationToTrim)
{
	Population output = populationToTrim;

	while(output.m_populationQueue.size() > getPopulationLimit())
		output.m_populationQueue.pop();

	return output;
}

Population GeneticAlgorithm::crossoverPopulation(std::list<std::pair<Individual, Individual>>& selectedParents)
{
	return Population();
}

Population GeneticAlgorithm::mutatePopulation(Population & population)
{
	return Population();
}

std::list<std::pair<Individual, Individual>> GeneticAlgorithm::selectParents()
{
	return std::list<std::pair<Individual, Individual>>();
}

std::list<Individual> GeneticAlgorithm::getSortedPopulation()
{
	Population tmp = m_population;

	std::list<Individual> output;

	while (!tmp.m_populationQueue.empty()) 
	{
		output.push_back(tmp.m_populationQueue.top());
		tmp.m_populationQueue.pop();
	}

	return output;
}

std::list<Individual> GeneticAlgorithm::rouletteSelection()
{
	return std::list<Individual>();
}

bool GeneticAlgorithm::verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount)
{
	return generationCount < m_generationLimit && generationWithoutImprovementCount < m_generationsWithoutImprovementLimit;
}

std::vector<int> GeneticAlgorithm::getGreedySolution(matrixGraph * graph)
{
	std::vector<int> output;
	output.push_back(0);
	int currRow = 0;
	while (output.size() != graph->getSize())
	{
		int minValue = -1;
		int minIndex;
		for (int i = 0; i < graph->getSize(); i++)
		{
			if (i == currRow)
				continue;
			if (graph->getConnectionValue(currRow, i) < minValue || minValue == -1)
			{
				auto result = std::find(output.begin(), output.end(), i);
				if (result != std::end(output))
					continue;
				minValue = graph->getConnectionValue(currRow, i);
				minIndex = i;
			}
		}
		output.push_back(minIndex);
		currRow = minIndex;
	}

	return output;
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

std::pair<Individual, Individual> GeneticAlgorithm::partialMappedCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b)
{
	std::vector<int> vFirst(firstParent.genotype.size()), vSecond(secondParent.genotype.size());

	std::fill(vFirst.begin(), vFirst.end(), -1);
	std::fill(vSecond.begin(), vSecond.end(), -1);

	// Partial copy
	for (int i = a; i <= b; i++)
	{
		vFirst[i] = secondParent.genotype[i];
		vSecond[i] = firstParent.genotype[i];
	}

	// Non-conflict copy
	for (int i = 0; i < vFirst.size(); i++)
	{
		if (i >= a && i <= b)
			continue;
		if (std::find(vFirst.begin(), vFirst.end(), firstParent.genotype[i]) == std::end(vFirst))
			vFirst[i] = firstParent.genotype[i];
		else
		{ 
			// Confilict copy
			for (int lookupIndex = 0; lookupIndex < vFirst.size(); lookupIndex++)
			{
				if (vFirst[lookupIndex] == firstParent.genotype[i])
				{
					vFirst[i] = firstParent.genotype[lookupIndex];
					break;
				}
			}
		}

		if (std::find(vSecond.begin(), vSecond.end(), secondParent.genotype[i]) == std::end(vSecond))
			vSecond[i] = secondParent.genotype[i];
		else
		{
			// Confilict copy
			for (int lookupIndex = 0; lookupIndex < vSecond.size(); lookupIndex++)
			{
				if (vSecond[lookupIndex] == secondParent.genotype[i])
				{
					vSecond[i] = secondParent.genotype[lookupIndex];
					break;
				}
			}
		}
	}

	Individual firstChild, secondChild;
	firstChild.setGenotype(vFirst, m_graph);
	secondChild.setGenotype(vSecond, m_graph);

	return std::make_pair(firstChild, secondChild);
}

std::pair<Individual, Individual> GeneticAlgorithm::orderCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b)
{
	return std::pair<Individual, Individual>();
}

std::pair<Individual, Individual> GeneticAlgorithm::cycleCrossover(Individual & firstParent, Individual & secondParent)
{
	return std::pair<Individual, Individual>();
}

void GeneticAlgorithm::initPopulation(matrixGraph* graph)
{
	std::vector<int> seed = getGreedySolution(graph);

	while(m_population.m_populationQueue.size() < getPopulationLimit())
	{
		Individual newIndividual;
		newIndividual.setGenotype(seed, graph);
		m_population.m_populationQueue.push(newIndividual);

		if (!std::next_permutation(seed.begin(), seed.end()))
		{
			throw std::logic_error("Population limit to huge for graph instance");
		}
	}
}

Individual Population::getFittest() const
{
	return Individual();
}
