#include "stdafx.h"
#include "GeneticAlgorithm.h"


Result GeneticAlgorithm::apply(matrixGraph * graph)
{
	using namespace std;
	setGraph(graph);

	// Initial settings
	setPopulationLimit((int)graph->getSize());
	setGenerationLimit((int)graph->getSize() * 3);
	setGenerationsWithoutImprovementLimit((int)graph->getSize()/2);
	this->m_tournamentSize = 5;// (int)(graph->getSize() / 7) + 1;
	this->m_mutationRate = 10;

	logData("Generating initial population");
	initPopulation(m_graph);
	size_t graphsize = m_graph->getSize();

	std::stringstream ss;
	ss << "Population generated with " << getPopulationUniqueRate() << " uniquness rate\n";
	logData(ss.str());

	int generationCount = 0;
	int generationsWithoutImprovement = 0;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	Individual bestIndividual = m_population.getFittest();
	logData("Current best solution: ");
	
	for (auto x : bestIndividual.genotype)
		ss << x << " ";
	ss << " : " << bestIndividual.cost << endl;

	logData(ss.str());
	logData("Starting main loop");

	startTime = std::chrono::high_resolution_clock::now();
	while (verifyEndingCondition(generationCount, generationsWithoutImprovement))
	{
		auto selected = selectParents();

		auto newPopulation = crossoverPopulation(selected);
		newPopulation = mutatePopulation(newPopulation);

		ss << "New population generated with " << getPopulationUniqueRate() << " uniquness rate\n";

		logData(ss.str());

		m_population = newPopulation;

		if (bestIndividual > m_population.getFittest())
		{
			bestIndividual = m_population.getFittest();
			ss << "New best solution: ";

			for (auto x : bestIndividual.genotype)
				ss << x << " ";
			ss << " : " << bestIndividual.cost;
			logData(ss.str());
			ss << "Generation nr: " << generationCount << "\n";
			ss << "Current population uniqness: " << getPopulationUniqueRate();

			logData(ss.str());

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

	m_population.populationList.clear();

	return output;
}

std::string GeneticAlgorithm::toString()
{
	std::string output;

	output.append("-");
	switch (getCrossoverType())
	{
	case CrossoverType::PMX:
		output.append("PMX-");
		break;
	case CrossoverType::OX:
		output.append("OX-");
		break;
	case CrossoverType::CX:
		output.append("CX-");
		break;
	}

	switch (getMutateType())
	{
	case MutateType::Invert:
		output.append("invert");
		break;
	case MutateType::Swap:
		output.append("swap");
		break;
	}

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

MutateType GeneticAlgorithm::getMutateType()
{
	return m_mutateType;
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

void GeneticAlgorithm::setLogging(bool logOn)
{
	m_logData = logOn;
}

Population GeneticAlgorithm::trimPopulation(Population & populationToTrim)
{
	Population output = populationToTrim;

	while (output.populationList.size() > getPopulationLimit())
		output.populationList.pop_back();

	return output;
}

Population GeneticAlgorithm::crossoverPopulation(std::vector<std::pair<Individual, Individual>>& selectedParents)
{
	Population output;
	switch (getCrossoverType())
	{
	case CrossoverType::OX:
		for (auto parent : selectedParents)
		{
			int a = rand() % m_graph->getSize();
			int b = rand() % m_graph->getSize();

			if (a > b)
				std::swap(a, b);

			auto children = orderCrossover(parent.first, parent.second, a, b);
			output.add(children.first);
			output.add(children.second);
		}
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
		if (rand() % 101 < m_mutationRate)
		{
			int a = rand() % currIndividual.genotype.size();
			int b = rand() % currIndividual.genotype.size();

			mutate(currIndividual, a, b);
		}
	}
	return population;
}

std::vector<std::pair<Individual, Individual>> GeneticAlgorithm::selectParents()
{
	auto output = tournamentSelection();
	return output;
}

std::vector<Individual> GeneticAlgorithm::getSortedPopulation()
{
	throw std::invalid_argument("not yet implemented");
	Population tmp = m_population;
	
	//tmp.populationList.sort();

	return tmp.populationList;
}

float GeneticAlgorithm::getPopulationUniqueRate()
{
	auto population = m_population.populationList;

	sort(population.begin(), population.end());
	auto uniqueCount = std::unique(population.begin(), population.end()) - population.begin();

	float uniquenessRate = ((float)uniqueCount) / (float)population.size();

	return uniquenessRate;
}

std::vector<std::pair<Individual, Individual>> GeneticAlgorithm::tournamentSelection()
{
	std::vector<std::pair<Individual, Individual>> output;

	while (output.size()*2 < getPopulationLimit())
	{
		std::vector<Individual> firstTorunament, secondTournament;

		while (firstTorunament.size() < m_tournamentSize)
			firstTorunament.push_back(m_population.populationList[rand() % m_population.populationList.size()]);
		
		while (secondTournament.size() < m_tournamentSize)
			secondTournament.push_back(m_population.populationList[rand() % m_population.populationList.size()]);

		Individual firstWinner, secondWinner;

		firstWinner = firstTorunament[0];
		secondWinner = secondTournament[0];
		for (int i = 0; i < firstTorunament.size(); i++)
		{
			if (firstWinner.cost > firstTorunament[i].cost)
				firstWinner = firstTorunament[i];

			if (secondWinner.cost > secondTournament[i].cost)
				secondWinner = secondTournament[i];
		}

		output.push_back(std::make_pair(firstWinner, secondWinner));
	}

	return output;
}


bool GeneticAlgorithm::verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount)
{
	return generationCount < m_generationLimit && generationWithoutImprovementCount < m_generationsWithoutImprovementLimit;
}

void GeneticAlgorithm::logData(std::string message, std::string function)
{
	if (m_logData)
	{
		if (!function.empty())
			std::cout << function << ": ";
		std::cout << message << std::endl;
	}
}

void GeneticAlgorithm::mutate(Individual & individual, int a, int b)
{
	switch (getMutateType())
	{
	case MutateType::Invert:
		invert(individual, a, b);
		break;
	case MutateType::Swap:
		std::swap(individual.genotype[a], individual.genotype[b]);
		break;
	}
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
	std::vector<int> firstPermutation(firstParent.genotype.size(), -1);
	std::vector<int> secondPermutation(firstParent.genotype.size(), -1);

	// Partial copy
	for (int i = a; i <= b; i++)
	{
		vFirst[i] = secondParent.genotype[i];
		vSecond[i] = firstParent.genotype[i];

		if (secondParent.genotype[i] != firstParent.genotype[i])
		{
			firstPermutation[secondParent.genotype[i]] = firstParent.genotype[i];
			secondPermutation[firstParent.genotype[i]] = secondParent.genotype[i];
		}
		else
		{
			firstPermutation[secondParent.genotype[i]] = -1;
			secondPermutation[firstParent.genotype[i]] = -1;
		}
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
	std::vector<bool> firstRemplacement(m_graph->getSize(), false);
	std::vector<bool> secondRemplacement(m_graph->getSize(), false);
	std::vector<int> firstChildVector(m_graph->getSize(), -1);
	std::vector<int> secondChildVector(m_graph->getSize(), -1);

	auto firstParentVector = firstParent.genotype;
	auto secondParentVector = secondParent.genotype;

	// In cut range
	for (int i = a; i <= b; i++)
	{
		firstChildVector[i] = firstParentVector[i];
		secondChildVector[i] = secondParentVector[i];

		firstRemplacement[firstParentVector[i]] = true;
		secondRemplacement[secondParentVector[i]] = true;
	}

	// Make copied part be last in vector
	int howFarToRotate = firstChildVector.size() - 1 - b;
	std::rotate(firstParentVector.rbegin(), firstParentVector.rbegin() + howFarToRotate, firstParentVector.rend());
	std::rotate(secondParentVector.rbegin(), secondParentVector.rbegin() + howFarToRotate, secondParentVector.rend());

	// Calculate copied area start index
	int copiedPartBeginIndex = a + howFarToRotate;

	int firstCopyLastIndex = 0;
	int secondCopyLastIndex = 0;

	// Copy part outside of range
 	for (int i = b + 1; i != a; i++)
	{
		if (i == m_graph->getSize())
		{
			if (a == 0)
				break;
			else
				i = 0;
		}

		for(int j = firstCopyLastIndex; j < secondParentVector.size(); j++)
			if (!firstRemplacement[secondParentVector[j]])
			{
				firstChildVector[i] = secondParentVector[j];
				firstRemplacement[secondParentVector[j]] = true;
				firstCopyLastIndex = j + 1;
				break;
			}

		for (int j = secondCopyLastIndex; j < firstParentVector.size(); j++)
			if (!secondRemplacement[firstParentVector[j]])
			{
				secondChildVector[i] = firstParentVector[j];
				secondRemplacement[firstParentVector[j]] = true;
				secondCopyLastIndex = j + 1;
				break;
			}
	}

	Individual firstChild, secondChild;
	firstChild.setGenotype(firstChildVector, m_graph);
	secondChild.setGenotype(secondChildVector, m_graph);

	return std::make_pair(firstChild, secondChild);
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

	for (int i = 0; i < b - a; i++)
	{
		std::swap(path[i + a], path[b - i]);
	}

	individual.setGenotype(path, m_graph);
}

void GeneticAlgorithm::initPopulation(matrixGraph* graph)
{
	Individual greedy;

	greedy.setGenotype(getGreedySolution(graph), graph);
	m_population.populationList.push_back(greedy);

	while(m_population.populationList.size() < getPopulationLimit())
	{
		Individual newIndividual;

		newIndividual.setGenotype(getRandomSolution(graph->getSize()), graph);

		int a = rand() % m_graph->getSize();
		int b = rand() % m_graph->getSize();

		if (a > b)
			std::swap(a, b);

		auto children = partialMappedCrossover(greedy, newIndividual,a,b);

		m_population.populationList.push_back(children.first);
		m_population.populationList.push_back(children.second);
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

bool Individual::operator==(const Individual & other) const
{
	return cost == other.cost && genotype == other.genotype;
}
