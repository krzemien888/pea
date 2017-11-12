#include "stdafx.h"

class TSPDataParserTests : public ::testing::Test
{
public:
	TSPDataParserTests() = default;
protected:
};


TEST_F(TSPDataParserTests, GeneralCoordParseTest)
{
	std::vector<std::vector<int>> m = {
		{0, 1, 2},
		{1, 0, 1},
		{2, 1, 0}
	};

	matrixGraph graph;
	graph.setMatrix(m);

	std::vector<std::string> s = { "1 1 0","2 2 0","3 3 0" };
	TSPHeader header;
	header.setType(TSP::Type::tsp);
	header.setWeightType(TSP::WeightType::euclidean2d);
	header.setDimension(3);
	
	TSPDataParser parser(header);
	parser.parse(s);
	auto result = parser.getGraph();

	ASSERT_EQ(result, graph);
}

