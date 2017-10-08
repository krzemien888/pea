#include "stdafx.h"

class matrixGraphTest : public ::testing::Test 
{
protected:
	matrixGraph graph;
	std::vector<std::vector<int>> vector2d =
	{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};;
};

TEST_F(matrixGraphTest, graphShouldBeInitializedEmpty)
{
	ASSERT_EQ(graph.getSize(), 0);
};

TEST_F(matrixGraphTest, graphShouldBeAbleToBeGeneratedFrom2dVector)
{
	graph.setMatrix(vector2d);

	for (size_t x = 0; x < vector2d.size(); x++)
		for (size_t y = 0; y < vector2d.size(); y++)
			ASSERT_EQ(vector2d[x][y], graph.getConnectionValue(x, y));
};

TEST_F(matrixGraphTest, graphShouldIncreaseSizeAndAccessDataAfterVertexAddition)
{
	int oldSize = graph.getSize();

	graph.addVertex();

	ASSERT_EQ(oldSize + 1, graph.getSize());
	ASSERT_EQ(graph.getConnectionValue(0, 0), 0);
};

TEST_F(matrixGraphTest, graphShouldChangeConnectionValue)
{
	graph.addVertex();
	graph.setConnection(0, 0, 5);
	ASSERT_EQ(graph.getConnectionValue(0, 0), 5);
};

TEST_F(matrixGraphTest, graphShouldReturnNeighbours)
{
	graph.setMatrix(vector2d);

	auto neighbours = graph.getNeighbours(0);

	ASSERT_EQ(neighbours, vector2d[0]);
};

TEST_F(matrixGraphTest, graphShouldBeComparable)
{
	graph.setMatrix(vector2d);
	matrixGraph otherGraph;
	otherGraph.setMatrix(vector2d);

	ASSERT_TRUE(graph == otherGraph);

	otherGraph.setConnection(0, 0, 29);

	ASSERT_FALSE(graph == otherGraph);
}