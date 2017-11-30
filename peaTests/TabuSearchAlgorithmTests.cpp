#include "stdafx.h"

TEST(TabuSearchAlgorithmTests, DebugTestCase)
{
	TabuSearchAlgorithm alg;

	std::vector<std::vector<int>> v = {
		{ 0,1,15,6 },
		{ 2,0,7,3 },
		{ 9,6,0,12 },
		{ 10,4,8,0 }
	};
	matrixGraph graph;
	graph.setMatrix(v);

	auto result = alg.apply(&graph);
	std::vector<int> rightPath = { 0,1,3,2 };
	ASSERT_EQ(result.path, rightPath);
	ASSERT_EQ(result.result, 21);
}
