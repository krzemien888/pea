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

TEST_F(matrixGraphTest, graphShouldIncreaseSizeAfterVertexAddition)
{
	int oldSize = graph.getSize();

	for(int i = 0; i < 5; i++)
		graph.addVertex();

	ASSERT_EQ(oldSize + 5, graph.getSize());
};

TEST_F(matrixGraphTest, graphShouldAccessDataAfterVertexAddition)
{
	int oldSize = graph.getSize();

	for (int i = 0; i < 5; i++)
		graph.addVertex();

	ASSERT_NO_THROW(graph.setConnection(0, 4, 5));
	ASSERT_NO_THROW(graph.getConnectionValue(0, 4));
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

TEST_F(matrixGraphTest, graphShouldReturnProperDensity)
{
	for (int i = 0; i < 10; i++)
		graph.addVertex();

	for (int i = 0; i < 5; i++)
		graph.setConnection(i, i + 1, 10);

	ASSERT_EQ(graph.getDensity(), (float)5 / (float)90);
}

TEST_F(matrixGraphTest, graphShouldBeGeneratedWithGivenVertexCount)
{
	auto graph = matrixGraph::generate(10, 0, 1, 20);

	ASSERT_EQ(graph.getSize(), 10);
}

TEST_F(matrixGraphTest, graphShouldBeGeneratedWithValuesBeetweenGivenRange)
{
	auto graph = matrixGraph::generate(10, 0.5);

	int max = 0, min = 100;
	for(unsigned int x = 0; x < graph.getSize(); x++)
		for (unsigned int y = 0; y < graph.getSize(); y++)
		{
			if (graph.getConnectionValue(x, y) > max)
				max = graph.getConnectionValue(x, y);
			if (graph.getConnectionValue(x, y) < min && graph.getConnectionValue(x, y) != 0)
				min = graph.getConnectionValue(x, y);
		}

	ASSERT_TRUE(max <= 20);
	ASSERT_TRUE(min >= 1);
}

TEST_F(matrixGraphTest, graphShouldBeGeneratedWithGivenDensity)
{
	auto graph = matrixGraph::generate(10, 0.50, 1, 20);

	ASSERT_EQ(graph.getDensity(), 0.50);
}