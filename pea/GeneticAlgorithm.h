#pragma once
#include "stdafx.h"
#include "IAlgorithm.h"
struct Individual
{
	std::vector<int> genotype;
	int cost;
	bool operator>(const Individual& other) const;

	void setGenotype(std::vector<int> newGenotype, matrixGraph * graph);
};

enum class CrossoverType {
	PMX, OX, CX
};

struct Population
{
	std::priority_queue<Individual, std::vector<Individual>, std::greater<Individual>> m_populationQueue;
	Individual getFittest() const;
	void add(Individual toAdd) { m_populationQueue.push(toAdd); };
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

	// Population operations
	Population trimPopulation(Population & populationToTrim);
	Population crossoverPopulation(std::list<std::pair<Individual, Individual>> & selectedParents);
	Population mutatePopulation(Population & population);
	std::list<std::pair<Individual, Individual>> selectParents();
	std::list<Individual> getSortedPopulation();

	// Selection operators
	std::list<Individual> rouletteSelection();

	// Crossover operators
	std::pair<Individual, Individual> partialMappedCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b);
	std::pair<Individual, Individual> orderCrossover(Individual & firstParent, Individual & secondParent, const int a, const int b);
	std::pair<Individual, Individual> cycleCrossover(Individual & firstParent, Individual & secondParent);

	// Mutate operators

	// Initialize methods
	void initPopulation(matrixGraph* graph);
private:

	// Properties

	// Algorithm settings
	int m_populationLimit;
	int m_generationLimit;
	int m_generationsWithoutImprovementLimit;
	CrossoverType m_crossoverType = CrossoverType::PMX;

	// Inner data properies
	Population m_population;
	matrixGraph* m_graph = nullptr;

	// Initialize methods
	bool verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount);
	std::vector<int> getGreedySolution(matrixGraph* graph);
};

