
#include "stdafx.h"

class TSPHeaderParserTests : public ::testing::Test
{
public:
	TSPHeaderParserTests() = default;
protected:
	TSPHeaderParser parser;
};

TEST_F(TSPHeaderParserTests, ParserShouldThrowInvalidArgumentIfUnknowParameterMeet)
{
	std::vector<std::string> s = { "invalidArgumentString" };
	ASSERT_THROW(auto header = parser.parse(s), std::invalid_argument);
};

TEST_F(TSPHeaderParserTests, ParseNameString) 
{
	auto header = parser.parse("NAME : NameOfDatafile");

	ASSERT_EQ(header.getName().compare("NameOfDatafile"), 0);
};


TEST_F(TSPHeaderParserTests, ParseTypeString) 
{
	auto header = parser.parse("TYPE : TSP");
	ASSERT_EQ(header.getType(), TSP::Type::tsp);

	header = parser.parse("TYPE : ATSP");
	ASSERT_EQ(header.getType(), TSP::Type::atsp);

	header = parser.parse("TYPE : SOP");
	ASSERT_EQ(header.getType(), TSP::Type::sop);

	header = parser.parse("TYPE : HCP");
	ASSERT_EQ(header.getType(), TSP::Type::hcp);

	header = parser.parse("TYPE : CVRP");
	ASSERT_EQ(header.getType(), TSP::Type::cvrp);

	header = parser.parse("TYPE : TOUR");
	ASSERT_EQ(header.getType(), TSP::Type::tour);

	ASSERT_THROW(header = parser.parse("TYPE : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseComment)
{
	auto header = parser.parse("COMMENT : ThisIsSomeTestingComment");

	ASSERT_TRUE(header.getComment() == "ThisIsSomeTestingComment");
}

TEST_F(TSPHeaderParserTests, ParseDimension)
{
	auto header = parser.parse("DIMENSION : 15");

	ASSERT_EQ(header.getDimension(), 15);
	ASSERT_THROW(header = parser.parse("DIMENSION : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseCapacity)
{
	auto header = parser.parse("CAPACITY : 15");

	ASSERT_EQ(header.getCapacity(), 15);
	ASSERT_THROW(header = parser.parse("CAPACITY : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseWeightType)
{
	auto header = parser.parse("EDGE_WEIGHT_TYPE : EXPLICIT");
	auto result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::explicitType);

	header = parser.parse("EDGE_WEIGHT_TYPE : EUC_2D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::euclidean2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : EUC_3D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::euclidean3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAX_2D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::max2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAX_3D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::max3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAN_2D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::man2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAN_3D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::man3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : CEIL_2D");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::ceil2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : GEO");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::geo);

	header = parser.parse("EDGE_WEIGHT_TYPE : ATT");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::att);

	header = parser.parse("EDGE_WEIGHT_TYPE : XRAY1");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::xray1);

	header = parser.parse("EDGE_WEIGHT_TYPE : XRAY2");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::xray2);

	header = parser.parse("EDGE_WEIGHT_TYPE : SPECIAL");
	result = header.getWeightType();
	ASSERT_EQ(result, TSP::WeightType::special);

	ASSERT_THROW(header = parser.parse("EDGE_WEIGHT_TYPE  : InvalidString");, std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseEdgeWeightFormat)
{
	auto header = parser.parse("EDGE_WEIGHT_FORMAT : FUNCTION");
	auto result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::function);

	header = parser.parse("EDGE_WEIGHT_FORMAT : FULL_MATRIX");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::fullMatrix);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_ROW");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::upperRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_ROW");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::lowerRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_DIAG_ROW");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::upperDiagRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_DIAG_ROW");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::lowerDiagRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_COL");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::upperCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_COL");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::lowerCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_DIAG_COL");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::upperDiagCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_DIAG_COL");
	result = header.getEdgeWeightFormat();
	ASSERT_EQ(result, TSP::EdgeWeightFormat::lowerDiagCol);

	ASSERT_THROW(header = parser.parse("EDGE_WEIGHT_FORMAT  : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseEdgeDataFormat)
{
	auto header = parser.parse("EDGE_DATA_FORMAT : EDGE_LIST");
	ASSERT_EQ(header.getEdgeDataFormat(), TSP::EdgeDataFormat::edgeList);

	header = parser.parse("EDGE_DATA_FORMAT : ADJ_LIST");
	ASSERT_EQ(header.getEdgeDataFormat(), TSP::EdgeDataFormat::adjList);

	ASSERT_THROW(header = parser.parse("EDGE_DATA_FORMAT  : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseNodeCoordType)
{
	auto header = parser.parse("NODE_COORD_TYPE : TWOD_COORDS");
	ASSERT_EQ(header.getNodeCoordType(), TSP::NodeCoordType::twodCoords);

	header = parser.parse("NODE_COORD_TYPE : THREED_COORDS");
	ASSERT_EQ(header.getNodeCoordType(), TSP::NodeCoordType::threedCoords);

	header = parser.parse("NODE_COORD_TYPE : NO_COORDS");
	ASSERT_EQ(header.getNodeCoordType(), TSP::NodeCoordType::noCoords);

	ASSERT_THROW(header = parser.parse("NODE_COORD_TYPE : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseDisplayDataType)
{
	auto header = parser.parse("DISPLAY_DATA_TYPE : COORD_DISPLAY");
	ASSERT_EQ(header.getDisplayDataType(), TSP::DisplayDataType::coordDisplay);

	header = parser.parse("DISPLAY_DATA_TYPE : TWOD_DISPLAY");
	ASSERT_EQ(header.getDisplayDataType(), TSP::DisplayDataType::twodDisplay);

	header = parser.parse("DISPLAY_DATA_TYPE : NO_DISPLAY");
	ASSERT_EQ(header.getDisplayDataType(), TSP::DisplayDataType::noDisplay);

	ASSERT_THROW(header = parser.parse("DISPLAY_DATA_TYPE : InvalidString"), std::invalid_argument);
}