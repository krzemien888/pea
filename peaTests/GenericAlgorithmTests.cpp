#include "stdafx.h"


TEST(GeneticAlgorithmTests, toStringShouldProperyGenerateIdentificationString)
{
	GeneticAlgorithm ga;

	ga.setCrossoverType(CrossoverType::PMX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(500);

	ASSERT_EQ("-PMX", ga.toString());

	ga.setCrossoverType(CrossoverType::OX);
	ga.setGenerationLimit(2000);
	ga.setGenerationsWithoutImprovementLimit(300);
	ga.setPopulationLimit(600);

	ASSERT_EQ("-OX", ga.toString());

	ga.setCrossoverType(CrossoverType::CX);
	ga.setGenerationLimit(1000);
	ga.setGenerationsWithoutImprovementLimit(200);
	ga.setPopulationLimit(500);

	ASSERT_EQ("-CX", ga.toString());
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
		population.populationList.push_back(newIndividual);
	}


	population = ga.trimPopulation(population);

	ASSERT_EQ(population.populationList.size(), 100);
}

TEST(GeneticAlgorithmTests, partialMappedCrossoverShouldCrossProperly)
{
	GeneticAlgorithm ga;
	auto graph = matrixGraph::generate(9, true);
	ga.setGraph(&graph);
	Individual first;
	Individual second;

	std::vector<int> firstParent = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> secondParent = { 3, 4, 1, 0, 7, 6, 5, 8, 2 };
	
	first.setGenotype(firstParent, &graph);
	second.setGenotype(secondParent, &graph);

	auto children = ga.partialMappedCrossover(first, second, 3, 6);

	std::vector<int> properFirstVector = { 3,1,2,0,7,6,5,4,8 };
	std::vector<int> properSecondVector = { 0, 7, 1, 3, 4, 5, 6, 8, 2 };
	ASSERT_EQ(children.first.genotype, properFirstVector);
	ASSERT_EQ(children.second.genotype, properSecondVector);
}

TEST(GeneticAlgorithmTests, partialMappedCrossShouldGenerateAcceptableSolutions)
{
	srand((unsigned int)time(NULL));
	GeneticAlgorithm ga;
	auto graph = matrixGraph::generate(10, true);
	ga.setGraph(&graph);

	for (int i = 0; i < 100; i++)
	{
		Individual firstParent, secondParent; 
		firstParent.setGenotype(ga.getRandomSolution(10), &graph);
		secondParent.setGenotype(ga.getRandomSolution(10), &graph);

		int a = rand() % 10, b = rand() % 10;

		if (a > b)
			std::swap(a, b);

		auto kids = ga.partialMappedCrossover(firstParent, secondParent, a,b);

		for (int j = 0; j < 10; j++)
		{
			for (int index = 0; index < 10; index++)
			{
				if(kids.first.genotype[index] == kids.first.genotype[j] && index != j)
					GTEST_FAIL() << "Non unique solution generated\nIteration:" << i << "\na:" << a << "\nb" << b ;
				if (kids.second.genotype[index] == kids.second.genotype[j] && index != j)
					GTEST_FAIL() << "Non unique solution generated\nIteration:" << i << "\na:" << a << "\nb" << b;
			}
		}
	}
}

TEST(GeneticAlgorithmTests, generateRandomSolutionShouldGenerateAcceptableSolutions)
{
	GeneticAlgorithm ga;

	for (int i = 0; i < 100; i++)
	{
		auto v = ga.getRandomSolution(100);

		sort(v.begin(), v.end());

		for (int x = 0; x < v.size() - 1; x++)
			if (v[x] == v[x + 1])
				GTEST_FAIL() << "Non unique solution generated";
	}
}



TEST(GeneticAlgorithmTests, generateGreedySolutionShouldGenerateAcceptableSolutions)
{
	GeneticAlgorithm ga;

	for (int i = 0; i < 100; i++)
	{
		auto graph = matrixGraph::generate(100, false);
		auto v = ga.getGreedySolution(&graph);

		sort(v.begin(), v.end());

		for (int x = 0; x < v.size() - 1; x++)
			if (v[x] == v[x + 1])
				GTEST_FAIL() << "Non unique solution generated";
	}
}

TEST(GeneticAlgorithmTests, orderCrossShouldGenerateAcceptableSolutions)
{
	srand((unsigned int)time(NULL));
	GeneticAlgorithm ga;
	auto graph = matrixGraph::generate(10, true);
	ga.setGraph(&graph);

	for (int i = 0; i < 100; i++)
	{
		Individual firstParent, secondParent;
		firstParent.setGenotype(ga.getRandomSolution(10), &graph);
		secondParent.setGenotype(ga.getRandomSolution(10), &graph);

		int a = rand() % 10, b = rand() % 10;

		if (a > b)
			std::swap(a, b);

		auto kids = ga.orderCrossover(firstParent, secondParent, a, b);


		sort(kids.first.genotype.begin(), kids.first.genotype.end());
		auto uniqueCountfirst = std::unique(kids.first.genotype.begin(), kids.first.genotype.end()) - kids.first.genotype.begin();

		sort(kids.second.genotype.begin(), kids.second.genotype.end());
		auto uniqueCount = std::unique(kids.second.genotype.begin(), kids.second.genotype.end()) - kids.second.genotype.begin();

		ASSERT_EQ(uniqueCountfirst, 10);
		ASSERT_EQ(uniqueCount, 10);
	}
}

TEST(GeneticAlgorithmTests, orderCrossoverShouldCrossProperly)
{
	auto graph = matrixGraph::generate(9, false);
	GeneticAlgorithm ga;
	ga.setGraph(&graph);

	std::vector<int> firstParentV = {0,1,2,3,4,5,6,7,8};
	std::vector<int> secondParentV = {3,4,1,0,7,6,5,8,2};

	Individual firstParent, secondParent;
	firstParent.setGenotype(firstParentV, &graph);
	secondParent.setGenotype(secondParentV, &graph);

	auto children = ga.orderCrossover(firstParent, secondParent, 3, 6);

	std::vector<int> firstChildV = {1,0,7,3,4,5,6,8,2};
	std::vector<int> secondChildV = { 2,3,4,0,7,6,5,8,1 };

	ASSERT_EQ(children.first.genotype, firstChildV);
	ASSERT_EQ(children.second.genotype, secondChildV);

}

TEST(GeneticAlgorithmTests, orderCrossoverShouldCrossProperly2)
{
	auto graph = matrixGraph::generate(10, false);
	GeneticAlgorithm ga;
	ga.setGraph(&graph);

	std::vector<int> firstParentV = {6,1,5,9,3,0,8,4,7,2 };
	std::vector<int> secondParentV = { 9,8,2,6,4,5,0,1,7,3 };

	Individual firstParent, secondParent;
	firstParent.setGenotype(firstParentV, &graph);
	secondParent.setGenotype(secondParentV, &graph);

	auto children = ga.orderCrossover(firstParent, secondParent, 4, 7);//3 6

	std::vector<int> firstChildV = { 2,6,5,1,3,0,8,4,7,9 };
	std::vector<int> secondChildV = { 6,9,3,8,4,5,0,1,7,2};

	ASSERT_EQ(children.first.genotype, firstChildV);
	ASSERT_EQ(children.second.genotype, secondChildV);

}
TEST(GeneticAlgorithmTests, cycleCrossoverShouldCrossProperly)
{
	ASSERT_FALSE(true);
}