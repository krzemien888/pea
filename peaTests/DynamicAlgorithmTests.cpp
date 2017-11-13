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