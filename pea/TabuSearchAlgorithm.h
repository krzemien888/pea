#pragma once
#include "IAlgorithm.h"
class TabuSearchAlgorithm :
	public IAlgorithm
{
public:
	virtual Result apply(matrixGraph* graph) override;
	virtual ~TabuSearchAlgorithm() = default;

	void setNeighbourhoodGenerationMethod(std::string method);
	void setTabuListSize(size_t size);
	void setCadenceLenght(int cadence);
private:

	struct Neighbour
	{
		int cityA, cityB, value;
		std::vector<int> solution;
	};

	struct TabuEntry
	{
		int cityA, cityB, value;

		bool operator==(const TabuEntry &entry)
		{
			return cityA == entry.cityA && cityB == entry.cityB && value == entry.value;
		}
	};

	enum class NeighbourhoodType {
		Insert,Invert,Swap
	};

	void initTabu(size_t size);
	std::vector<int> getStartingSolution(size_t size);
	std::vector<int> getRandomSolution(size_t size);
	std::vector<Neighbour> getNeighbourhood(std::vector<int> &starter, const int currBestValue);
	Neighbour getBestNeighbour(std::vector<Neighbour> &solutions);
	int calculatePathValue(std::vector<int> path);

	bool verifyTabuList(Neighbour& neighbour);
	void decrementTabu();
	void setTabu(int cityA, int cityB);

	Neighbour neighbourByInsert(std::vector<int> solution, int a, int b);
	Neighbour neighbourBySwap(std::vector<int> solution, int a, int b);
	Neighbour neighbourByInvert(std::vector<int> solution, int a, int b);

	matrixGraph * m_graph;
	std::list<TabuSearchAlgorithm::TabuEntry> m_tabu;
	int startCadence = 0;
	int iterationCount = 20;
	size_t tabuSize = 0;

	NeighbourhoodType selectedType = NeighbourhoodType::Invert;
};

