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

	startTime = std::chrono::high_resolution_clock::now();

	int iterationsSinceSwitch = 0;
	while(iterationsSinceSwitch < 100)
	{

		auto neighbourhood = getNeighbourhood(currBest);
		Neighbour bestNeighbour = getBestNeighbour(neighbourhood);
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

void TabuSearchAlgorithm::initTabu(size_t size)
{
	m_tabu.resize(size);
	for (auto &row : m_tabu)
		row.resize(size);

	startCadence = (int)floor(((float)size) / 2);
}

std::vector<int> TabuSearchAlgorithm::getStartingSolution(size_t size)
{
	std::vector<int> output(size);
	std::iota(std::begin(output), std::end(output), 0);
	return output;
}

std::vector<TabuSearchAlgorithm::Neighbour> TabuSearchAlgorithm::getNeighbourhood(std::vector<int> starter)
{
	std::vector<Neighbour> output;

	for(int x = 0; x < starter.size(); x++)
		for (int y = x + 1; y < starter.size(); y++)
			output.push_back(neighbourBySwap(starter, x, y));

	return output;
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::getBestNeighbour(std::vector<Neighbour> neighbourhood)
{
	Neighbour bestNeighbour = neighbourhood[0];

	for (auto& neighbour : neighbourhood)
		if (neighbour.value < bestNeighbour.value && verifyTabuList(neighbour))
			bestNeighbour = neighbour;

	return bestNeighbour;
}

bool TabuSearchAlgorithm::verifyTabuList(Neighbour & neighbour)
{
	return m_tabu[neighbour.cityA][neighbour.cityB] == 0;
}

void TabuSearchAlgorithm::decrementTabu()
{
	for (auto& row : m_tabu)
		for (auto &value : row)
			value -= (value == 0) ? 0 : 1;
}

void TabuSearchAlgorithm::setTabu(int cityA, int cityB)
{
	m_tabu[cityA][cityB] += startCadence;
}

TabuSearchAlgorithm::Neighbour TabuSearchAlgorithm::neighbourByInsert(std::vector<int> solution, int a, int b)
{
	Neighbour output;
	output.solution = solution;
	
	if (a < b)
	{
		for (int i = a + 1; i <= b; i++)
			output.solution[i] = solution[i - 1];
		output.solution[a + 1] = solution[b];
	}
	else
	{
		for (int i = b; i < a; i++)
			output.solution[i] = output.solution[i + 1];
		output.solution[a] = solution[b];
	}

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
