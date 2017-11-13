#include "stdafx.h"
#include "peaInclude.h"

TEST(DynamicAlgorithmTests, AlgorithmShouldReturnProperRouteValue)
{
	DynamicAlgorithm alg;

	std::vector<std::vector<int>> v = {
		{0,1,15,6},
		{2,0,7,3},
		{9,6,0,12},
		{10,4,8,0}
	};
	matrixGraph graph;
	graph.setMatrix(v);

	auto result = alg.apply(&graph);
	std::vector<int> rightPath = { 0,1,3,2 };
	ASSERT_EQ(result.path, rightPath);
	ASSERT_EQ(result.result, 21);
}

TEST(DynamicAlgorithmTests, AlgorithmPathAndValueShouldBeSameAsBruteforce)
{
	DynamicAlgorithm algDP;
	BruteforceAlgorithm algBrute;
	auto graph = matrixGraph::generate(9, true);

	auto dpResult = algDP.apply(&graph);
	auto bruteResult = algBrute.apply(&graph);

	ASSERT_EQ(dpResult.path, bruteResult.path);
	ASSERT_EQ(dpResult.result, dpResult.result);

}

TEST(DynamicAlgorithmTests, ShouldSolveInstancegr17)
{
	DynamicAlgorithm algDP;
	TSPFileReader reader;
	reader.setFileName("gr17.tsp");
	reader.tryParse();
	auto graph = reader.getData();

	auto dpResult = algDP.apply(&graph);

	std::vector<int> properPath = {
		0,11,16,8,7,4,3,15,14,6,5,12,10,9,1,13,2 };
	ASSERT_EQ(dpResult.path, properPath);
	ASSERT_EQ(dpResult.result, 39);

}


TEST(DynamicAlgorithmTests, ShouldSolveInstancegr21)
{
	DynamicAlgorithm algDP;
	TSPFileReader reader;
	reader.setFileName("gr21.tsp");
	reader.tryParse();
	auto graph = reader.getData();

	auto dpResult = algDP.apply(&graph);

	std::vector<int> properPath = {
				0, 15, 10, 2, 6, 5, 23, 7, 20, 4, 9, 16, 21, 17, 18, 14, 1, 19, 13, 12, 8, 22, 3, 11 };

	ASSERT_EQ(dpResult.path, properPath);
	ASSERT_EQ(dpResult.result, 2707);

}

TEST(DynamicAlgorithmTests, ShouldSolveInstancegr24)
{
	DynamicAlgorithm algDP;
	TSPFileReader reader;
	reader.setFileName("gr24.tsp");
	reader.tryParse();
	auto graph = reader.getData();

	auto dpResult = algDP.apply(&graph);

	std::vector<int> properPath = {
		0, 11,3,22,8,12,13,19,1,14,18,17,21,16,9,4,20,7,23,5,6,2,10,15 };

	ASSERT_EQ(dpResult.path, properPath);
	ASSERT_EQ(dpResult.result, 1272);

}