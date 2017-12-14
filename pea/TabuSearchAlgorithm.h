#pragma once
#include "IAlgorithm.h"
class TabuSearchAlgorithm :
	public IAlgorithm
{
public:
	virtual Result apply(matrixGraph* graph) override;
	virtual ~TabuSearchAlgorithm() = default;

private:

	struct Neighbour
	{
		int cityA, cityB, value;
		std::vector<int> solution;
	};

	void initTabu(size_t size);
	std::vector<int> getStartingSolution(size_t size);
	std::vector<TabuSearchAlgorithm::Neighbour> getNeighbourhood(Neighbour & starter);
	TabuSearchAlgorithm::Neighbour getBestNeighbour(std::vector<Neighbour>& neighbourhood);
	int calculatePathValue(std::vector<int> path);

	bool verifyTabuList(Neighbour& neighbour);
	void decrementTabu();
	void setTabu(int cityA, int cityB);
	void setTabu(Neighbour &neighbour);

	Neighbour neighbourByInsert(std::vector<int> solution, int a, int b);
	Neighbour neighbourBySwap(std::vector<int> solution, int a, int b);
	Neighbour neighbourByInvert(std::vector<int> solution, int a, int b);

	matrixGraph * m_graph;
	std::vector <std::vector<int>> m_tabu;
	int startCadence;
	int iterationCount = 20;
	bool isTabuFull = false;
	bool isTabuEmpty = true;
};

