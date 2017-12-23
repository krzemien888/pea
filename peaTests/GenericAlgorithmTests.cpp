#include "stdafx.h"


TEST(GeneticAlgorithmTests, toStringShouldProperyGenerateIdentificationString)
{
	GeneticAlgorithm ga;

	ga.setCrossoverType(CrossoverType::PMX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(500);

	ASSERT_EQ("-PMX-1000-200-500", ga.toString());

	ga.setCrossoverType(CrossoverType::OX);
	ga.setGenerationLimit(2000);
	ga.setGenerationsWithoutImprovementLimit(300);
	ga.setPopulationLimit(600);

	ASSERT_EQ("-OX-2000-300-600", ga.toString());

	ga.setCrossoverType(CrossoverType::CX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(500);

	ASSERT_EQ("-CX-1000-200-500", ga.toString());
}

TEST(GeneticAlgorithmTests, initPopulationShouldGenerateSeedPopulation)
{
	GeneticAlgorithm ga;
	ga.setCrossoverType(CrossoverType::CX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(500);

	ga.initPopulation();
	auto population = ga.getSortedPopulation();

	ASSERT_FALSE(population.empty());
	ASSERT_EQ(population.size(), 500);
}

TEST(GenericAlgorithmTests, TrimPopulationShouldBringDownPopulationToPopulationLimit)
{
	GeneticAlgorithm ga;
	auto graph = matrixGraph::generate(20, false);
	ga.setPopulationLimit(100);

	Population population;
	std::vector<int> v(20);
	std::iota(std::begin(v), std::end(v), 0);
	for (int i = 0; i < 200; i++)
	{
		std::next_permutation(v.begin(), v.end());
		Individual newIndividual;
		newIndividual.setGenotype(v, &graph);
		population.m_populationQueue.push(newIndividual);
	}


	auto population = ga.trimPopulation(population);

	ASSERT_EQ(population.m_populationQueue.size(), 100);
}

TEST(GeneticAlgorithmTests, getSortedPopulationShouldReturnSortedPopulation)
{
	GeneticAlgorithm ga;
	ga.setCrossoverType(CrossoverType::CX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(50);

	ga.initPopulation();
	auto population = ga.getSortedPopulation();

	ASSERT_FALSE(population.empty());

	while (!population.empty())
	{
		auto first = population.front();
		population.pop_front();
		auto second = population.front();
		ASSERT_FALSE(second.cost < first.cost);
	}
}

TEST(GenticAlgorithmTests, rouletteSelectionShouldReturnProperlySelectedParents)
{
	ASSERT_FALSE(true);
}

TEST(GeneticAlgorithmTests, partialMappedCrossoverShouldCrossProperly)
{
	ASSERT_FALSE(true);
}

TEST(GeneticAlgorithmTests, orderCrossoverShouldCrossProperly)
{
	ASSERT_FALSE(true);
}

TEST(GeneticAlgorithmTests, cycleCrossoverShouldCrossProperly)
{
	ASSERT_FALSE(true);
}