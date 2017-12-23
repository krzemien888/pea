#pragma once
#include "stdafx.h"
#include "IAlgorithm.h"

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
	std::pair<Individual, Individual> partialMappedCrossover(Individual & firstParent, Individual & secondParent);
	std::pair<Individual, Individual> orderCrossover(Individual & firstParent, Individual & secondParent);
	std::pair<Individual, Individual> cycleCrossover(Individual & firstParent, Individual & secondParent);

	// Mutate operators

	// Initialize methods
	void initPopulation();
private:

	// Properties

	// Algorithm settings
	int m_populationLimit;
	int m_generationLimit;
	int m_generationsWithoutImprovementLimit;
	CrossoverType m_crossoverType;

	// Inner data properies
	Population m_population;

	// Initialize methods
	std::pair<Individual, Individual> crossover(Individual & firstParent, Individual & secondParent);
	bool verifyEndingCondition(const int & generationCount, const int & generationWithoutImprovementCount);
};


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
};