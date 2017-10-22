
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
	ASSERT_THROW(auto header = parser.parse("invalidArgumentString"), std::invalid_argument);
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
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::explicitType);

	header = parser.parse("EDGE_WEIGHT_TYPE : EUC_2D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::euclidean2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : EUC_3D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::euclidean3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAX_2D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::max2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAX_3D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::max3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAN_2D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::man2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : MAN_3D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::man3d);

	header = parser.parse("EDGE_WEIGHT_TYPE : CEIL_2D");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::ceil2d);

	header = parser.parse("EDGE_WEIGHT_TYPE : GEO");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::geo);

	header = parser.parse("EDGE_WEIGHT_TYPE : ATT");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::att);

	header = parser.parse("EDGE_WEIGHT_TYPE : XRAY1");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::xray1);

	header = parser.parse("EDGE_WEIGHT_TYPE : XRAY2");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::xray2);

	header = parser.parse("EDGE_WEIGHT_TYPE : SPECIAL");
	ASSERT_EQ(header.getWeightType(), TSP::WeightType::special);

	ASSERT_THROW(header = parser.parse("EDGE_WEIGHT_TYPE  : InvalidString"), std::invalid_argument);
}

TEST_F(TSPHeaderParserTests, ParseEdgeWeightFormat)
{
	auto header = parser.parse("EDGE_WEIGHT_FORMAT : FUNCTION");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::function);

	header = parser.parse("EDGE_WEIGHT_FORMAT : FULL_MATRIX");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::fullMatrix);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_ROW");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::upperRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_ROW");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::lowerRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_DIAG_ROW");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::upperDiagRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_DIAG_ROW");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::lowerDiagRow);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_COL");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::upperCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_COL");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::lowerCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : UPPER_DIAG_COL");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::upperDiagCol);

	header = parser.parse("EDGE_WEIGHT_FORMAT : LOWER_DIAG_COL");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::EdgeWeightFormat::lowerDiagCol);

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
	auto header = parser.parse("DISPLAY_DATA_TYPE : COORDS_DISPLAY");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::DisplayDataType::coordDisplay);

	header = parser.parse("DISPLAY_DATA_TYPE : TWOD_DISPLAY");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::DisplayDataType::twodDisplay);

	header = parser.parse("DISPLAY_DATA_TYPE : NO_DISPLAY");
	ASSERT_EQ(header.getEdgeWeightFormat(), TSP::DisplayDataType::noDisplay);

	ASSERT_THROW(header = parser.parse("DISPLAY_DATA_TYPE : InvalidString"), std::invalid_argument);
}