#pragma once
#include "stdafx.h"
#include "IAlgorithm.h"
struct Individual
{
	std::vector<int> genotype;
	int cost;
	bool operator>(const Individual& other) const;
	bool operator<(const Individual& other) const;
	bool operator==(const Individual& other) const;
	void setGenotype(std::vector<int> newGenotype, matrixGraph * graph);
};

enum class CrossoverType {
	PMX, OX, CX
};

struct Population
{
	std::vector<Individual> populationList;
	Individual getFittest() const;
	void add(Individual toAdd) { populationList.push_back(toAdd); };
};

class GeneticAlgorithm :
	public IAlgorithm
{
public:
	// Constructors & destructors
	virtual ~GeneticAlgorithm() = default;

	// Algorithm interface
	virtual Result apply(matrixGraph* graph) override;
	virtual std::string toString() override;

	// Setters and getters
	void setPopulationLimit(const int newPopulationLimit);
	int getPopulationLimit() const;

	void setGenerationLimit(const int newGenerationLimit);
	int getGenerationLimit() const;

	void setGenerationsWithoutImprovementLimit(const int newLimit);
	int getGenerationswithoutImprovementLimit() const;

	void setGraph(matrixGraph* graph);

	std::vector<int> getRandomSolution(size_t size);

	void setCrossoverType(const CrossoverType & selectedType);
	CrossoverType getCrossoverType() const;

	void setLogging(bool logOn);

	// Population operations
	Population trimPopulation(Population & populationToTrim);
	Population crossoverPopulation(std::vector<std::pair<Individual, Individual>> & selectedParents);
	Population mutatePopulation(Population & population);
	std::vector<std::pair<Individual, Individual>> selectParents();
	std::vector<Individual> getSortedPopulation();
	float getPopulationUniqueRate();

	// Selection operators
	std::vector<std::pair<Individual, Individual>> tournamentSelection();

	// Crossover operators
	std::pair<Individual, Individual> partialMappedCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b);
	std::pair<Individual, Individual> orderCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b);
	std::pair<Individual, Individual> cycleCrossover(Individual & firstParent, Individual & secondParent);

	// Mutate operators
	void invert(Individual & individual, int a, int b);

	// Initialize methods
	void initPopulation(matrixGraph* graph);
	std::vector<int> getGreedySolution(matrixGraph* graph);
private:

	// Properties

	bool m_logData = true;

	// Algorithm settings
	int m_populationLimit;
	int m_generationLimit;
	int m_generationsWithoutImprovementLimit;
	int m_tournamentSize;
	int m_mutationRate;
	CrossoverType m_crossoverType = CrossoverType::PMX;

	// Inner data properies
	Population m_population;
	matrixGraph* m_graph = nullptr;

	// Initialize methods
	bool verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount);

	// Utility methods
	void logData(std::string message, std::string function = std::string(""));
};

