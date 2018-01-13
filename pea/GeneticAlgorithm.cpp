#include "stdafx.h"
#include "GeneticAlgorithm.h"


Result GeneticAlgorithm::apply(matrixGraph * graph)
{
	using namespace std;
	setGraph(graph);

	// Initial settings
	setPopulationLimit(graph->getSize() * 3);
	setGenerationLimit(pow(graph->getSize(), 3));
	setGenerationsWithoutImprovementLimit(graph->getSize() * 10);


	cout << "Generating initial population\n";
	initPopulation(graph);
	cout << "Population generated\n";
	int generationCount = 0;
	int generationsWithoutImprovement = 0;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;


	Individual bestIndividual = m_population.getFittest();
	cout << "Current best solution: ";
	
	for (auto x : bestIndividual.genotype)
		cout << x << " ";
	cout << " : " << bestIndividual.cost << endl;

	cout << "Starting main loop\n";

	startTime = std::chrono::high_resolution_clock::now();
	while (verifyEndingCondition(generationCount, generationsWithoutImprovement))
	{
		auto selected = selectParents();
		auto newPopulation = crossoverPopulation(selected);
		newPopulation = mutatePopulation(newPopulation);
			
		m_population = trimPopulation(newPopulation);

		if (bestIndividual > m_population.getFittest())
		{
			bestIndividual = m_population.getFittest();
			cout << "New best solution: ";

			for (auto x : bestIndividual.genotype)
				cout << x << " ";
			cout << " : " << bestIndividual.cost << endl;
			 
			cout << "Generation nr: " << generationCount << "\n";
			generationsWithoutImprovement = 0;
		}
		else {
			generationsWithoutImprovement++;

		}

		generationCount++;
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

std::vector<int> GeneticAlgorithm::getRandomSolution(size_t size)
{
	std::vector<int> tmp(size), output;
	std::iota(std::begin(tmp), std::end(tmp), 0);
	while (!tmp.empty())
	{
		int index = rand() % tmp.size();
		output.push_back(tmp[index]);
		tmp.erase(tmp.begin() + index);
	}

	return output;
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

	while (output.populationList.size() > getPopulationLimit())
		output.populationList.pop_back();

	return output;
}

Population GeneticAlgorithm::crossoverPopulation(std::list<std::pair<Individual, Individual>>& selectedParents)
{
	Population output;
	switch (getCrossoverType())
	{
	case CrossoverType::OX:

		break;
	case CrossoverType::CX:
		break;
	case CrossoverType::PMX:
		for (auto parent : selectedParents)
		{
			int a = rand() % m_graph->getSize();
			int b = rand() % m_graph->getSize();

			if (a > b)
				std::swap(a, b);

			auto children = partialMappedCrossover(parent.first, parent.second, a, b );
			output.add(children.first);
			output.add(children.second);
		}
		break;
	}
	return output;
}

Population GeneticAlgorithm::mutatePopulation(Population & population)
{
	for (auto &currIndividual : population.populationList)
	{
		if (rand() % 101 < 10)
		{
			int a = rand() % currIndividual.genotype.size();
			int b = rand() % currIndividual.genotype.size();
			invert(currIndividual, a, b);
		}
	}
	return population;
}

std::list<std::pair<Individual, Individual>> GeneticAlgorithm::selectParents()
{
	std::list<std::pair<Individual, Individual>> output;

	auto currPopulation = getSortedPopulation();

	while (output.size() < m_populationLimit/2)
	{
		auto first = currPopulation.front();
		currPopulation.pop_front();
		auto second = currPopulation.front();
		currPopulation.pop_front();
		output.push_back(std::make_pair(first, second));
	}
	
	return output;
}

std::list<Individual> GeneticAlgorithm::getSortedPopulation()
{
	Population tmp = m_population;
	
	tmp.populationList.sort();

	return tmp.populationList;
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
	std::vector<int> firstPermutation(firstParent.genotype.size());
	std::vector<int> secondPermutation(firstParent.genotype.size());

	std::fill(firstPermutation.begin(), firstPermutation.end(), -1);
	std::fill(secondPermutation.begin(), secondPermutation.end(), -1);

	// Partial copy
	for (int i = a; i <= b; i++)
	{
		vFirst[i] = secondParent.genotype[i];
		vSecond[i] = firstParent.genotype[i];

		firstPermutation[secondParent.genotype[i]] = firstParent.genotype[i];
		secondPermutation[firstParent.genotype[i]] = secondParent.genotype[i];
	}

	for (int i = 0; i < firstParent.genotype.size(); i++)
	{
		// Avoid already copied part
		if (i >= a && i <= b)
			continue;

		int firstParentPoint = firstParent.genotype[i];
		int firstSwitchPoint = firstPermutation[firstParentPoint];

		int secondParentPoint = secondParent.genotype[i];
		int secondSwitchPoint = secondPermutation[secondParentPoint];

		while (firstSwitchPoint != -1)
		{
			firstParentPoint = firstSwitchPoint;
			firstSwitchPoint = firstPermutation[firstSwitchPoint];
		}

		while (secondSwitchPoint != -1)
		{
			secondParentPoint = secondSwitchPoint;
			secondSwitchPoint = secondPermutation[secondSwitchPoint];
		}

		vFirst[i] = firstParentPoint;
		vSecond[i] = secondParentPoint;
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

void GeneticAlgorithm::invert(Individual & individual, int a, int b)
{
	if (a > b)
		std::swap(a, b);

	auto path = individual.genotype;

	for (int i = 0; i + a <= b; i++)
		path[i + a] = path[b - i];

	individual.setGenotype(path, m_graph);
}

void GeneticAlgorithm::initPopulation(matrixGraph* graph)
{
	Individual greedy;
	greedy.setGenotype(getGreedySolution(graph), graph);

	while(m_population.populationList.size() < getPopulationLimit())
	{
		Individual newIndividual;

		newIndividual.setGenotype(getRandomSolution(graph->getSize()), graph);
		m_population.populationList.push_back(newIndividual);
	}
}

Individual Population::getFittest() const
{
	auto best = populationList.front();
	
	for (auto &curr : populationList)
		if (best.cost > curr.cost)
			best = curr;
	
	return best;
}

bool Individual::operator<(const Individual& other) const
{
	return cost < other.cost;
}