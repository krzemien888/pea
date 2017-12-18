#include "stdafx.h"
#include "TabuSearchAlgorithm.h"

Result TabuSearchAlgorithm::apply(matrixGraph * graph)
{
	m_graph = graph;
	initTabu(graph->getSize());

	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	std::vector<int> currBest = getStartingSolution(graph->getSize());
	int currBestValue = calculatePathValue(currBest);

	std::vector<int> localBest = currBest;
	int localBestValue = currBestValue;

	startTime = std::chrono::high_resolution_clock::now();

	int iterationsSinceSwitch = 0;
	while(iterationsSinceSwitch < 100)
	{
		if (iterationsSinceSwitch == 50 || iterationsSinceSwitch == 75)
		{
			localBest = getRandomSolution(graph->getSize());
			localBestValue = calculatePathValue(localBest);
		}

		auto neighbourhood = getNeighbourhood(localBest, currBestValue);
		Neighbour bestNeighbour = getBestNeighbour(neighbourhood);
		localBest = bestNeighbour.solution;
		int bestMoveA = 0, bestMoveB = 0;
	
		if (bestNeighbour.value < currBestValue)
		{
			currBest = bestNeighbour.solution;
			currBestValue = bestNeighbour.value;
			bestMoveA = bestNeighbour.cityA;
			bestMoveB = bestNeighbour.cityB;
			iterationsSinceSwitch = 0;
		}
		else
			iterationsSinceSwitch++;
		
		decrementTabu();
		setTabu(bestMoveA, bestMoveB);
	}

	endTime = std::chrono::high_resolution_clock::now();
	Result output;
	output.fileName = graph->getName();
	output.path = currBest;
	output.result = currBestValue;
	output.time = (int)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

	m_tabu.clear();

	return output;
}

void TabuSearchAlgorithm::setNeighbourhoodGenerationMethod(std::string method)
{
	if (method == "invert")
		selectedType = NeighbourhoodType::Invert;
	else if (method == "swap")
		selectedType = NeighbourhoodType::Swap;
	else if (method == "insert")
		selectedType = NeighbourhoodType::Insert;
	else
		throw std::invalid_argument("Invalid string method for neighbourhood generation");
}

void TabuSearchAlgorithm::setTabuListSize(size_t size)
{
	tabuSize = size;
}

void TabuSearchAlgorithm::setCadenceLenght(int cadence)
{
	startCadence = cadence;
}

void TabuSearchAlgorithm::initTabu(size_t size)
{

	if(tabuSize != 0)
		tabuSize = size * 3;
	if(startCadence != 0)
		startCadence = (int)floor(((float)size) / 2);
}

std::vector<int> TabuSearchAlgorithm::getStartingSolution(size_t size)
{
	std::vector<int> output;
	output.push_back(0);
	int currRow = 0;
	while (output.size() != size)
	{
		int minValue = -1;
		int minIndex;
		for (int i = 0; i < m_graph->getSize(); i++)
		{
			if (i == currRow)
				continue;
			if (m_graph->getConnectionValue(currRow, i) < minValue || minValue == -1)
			{
				auto result = std::find(output.begin(), output.end(), i);
				if (result != std::end(output))
					continue;
				minValue = m_graph->getConnectionValue(currRow, i);
				minIndex = i;
			}
		}
		output.push_back(minIndex);
		currRow = minIndex;
	}

	return output;
}

std::vector<int> TabuSearchAlgorithm::getRandomSolution(size_t size)
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

std::vector<TabuSearchAlgorithm::Neighbour> TabuSearchAlgorithm::getNeighbourhood(std::vector<int> &starter, const int currBestValue)
{
	std::vector<Neighbour> output;
	for(int x = 0; x < starter.size(); x++)
		for (int y = x + 1; y < starter.size(); y++)
		{
			Neighbour newNeighbour;
			switch (selectedType)
			{
			case NeighbourhoodType::Swap:
				newNeighbour = neighbourBySwap(starter, x, y);
				break;
			case NeighbourhoodType::Insert:
				newNeighbour = neighbourByInsert(starter, x, y);
				break;
			case NeighbourhoodType::Invert:
				newNeighbour = neighbourByInvert(starter, x, y);
				break;
			}

			if (verifyTabuList(newNeighbour) || currBestValue > newNeighbour.value)
				output.push_back(newNeighbour);
		}

	return output;
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::getBestNeighbour(std::vector<Neighbour> &neighbourhood)
{
	Neighbour bestNeighbour = neighbourhood[0];
	bool aspiration = false;

	for (auto& neighbour : neighbourhood)
		if (neighbour.value < bestNeighbour.value)
			bestNeighbour = neighbour;
	return bestNeighbour;
}

bool TabuSearchAlgorithm::verifyTabuList(Neighbour & neighbour)
{
	for (auto entry : m_tabu)
	{
		if ((entry.cityA == neighbour.cityA && entry.cityB == neighbour.cityB)
			|| (entry.cityB == neighbour.cityA && entry.cityA == neighbour.cityB))
			return false;
	}
	return true;
}

void TabuSearchAlgorithm::decrementTabu()
{
	auto i = m_tabu.begin();
	while (i != m_tabu.end())
	{
		if (i->value == 1)
			i = m_tabu.erase(i);
		else if (i->value > 1)
			(i++)->value--;		
		
	}
}

void TabuSearchAlgorithm::setTabu(int cityA, int cityB)
{
	TabuEntry newEntry;
	newEntry.cityA = cityA;
	newEntry.cityB = cityB;
	newEntry.value = startCadence;
	m_tabu.push_back(newEntry);

	if (m_tabu.size() > tabuSize)
		m_tabu.pop_front();
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::neighbourByInsert(std::vector<int> solution, int a, int b)
{
	Neighbour output;
	output.solution = solution;
	
	if (a > b)
		std::swap(a, b);

	for (int i = a + 1; i <= b; i++)
		output.solution[i] = solution[i - 1];
	output.solution[a] = solution[b];
	
	output.cityA = a;
	output.cityB = b;
	output.value = calculatePathValue(output.solution);
	return output;
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::neighbourBySwap(std::vector<int> solution, int a, int b)
{
	Neighbour output;
	output.solution = solution;
	output.solution[a] = solution[b];
	output.solution[b] = solution[a];
	output.cityA = a;
	output.cityB = b;
	output.value = calculatePathValue(output.solution);
	return output;
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::neighbourByInvert(std::vector<int> solution, int a, int b)
{
	int from = (a > b) ? b : a;
	int to = (a > b)?  a : b;
	Neighbour output;
	output.solution = solution;

	for (int i = 0; i + from <= to; i++)
		output.solution[i + from] = solution[to - i];
	output.cityA = a;
	output.cityB = b;
	output.value = calculatePathValue(output.solution);

	return output;
}

int TabuSearchAlgorithm::calculatePathValue(std::vector<int> path)
{
	int result = 0;

	for (int index = 0; index < path.size() -1 ; index++)
		result += m_graph->getConnectionValue(path[index], path[index + 1]);

	result += m_graph->getConnectionValue(path[path.size() - 1], path[0]);

	return result;
}
