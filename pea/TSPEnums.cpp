#include "stdafx.h"
#include "TSPEnums.h"
namespace TSP 
{
	std::string toString(WeightType in)
	{
		std::string output;
		switch (in)
		{
		case WeightType::notSet:
			output = "NOT_SET";
			break;
		case WeightType::explicitType:
			output = "EXPLICIT";
			break;
		case WeightType::euclidean2d:
			output = "EUC_2D";
			break;
		case WeightType::euclidean3d:
			output = "EUC_3D";
			break;
		case WeightType::max2d:
			output = "MAX_2D";
			break;
		case WeightType::max3d:
			output = "MAX_3D";
			break;
		case WeightType::man2d:
			output = "MAN_2D";
			break;
		case WeightType::man3d:
			output = "MAN_3D";
			break;
		case WeightType::ceil2d:
			output = "CEIL_2D";
			break;
		case WeightType::geo:
			output = "GEO";
			break;
		case WeightType::att:
			output = "ATT";
			break;
		case WeightType::xray1:
			output = "XRAY1";
			break;
		case WeightType::xray2:
			output = "XRAY2";
			break;
		case WeightType::special:
			output = "SPECIAL";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}

	std::string toString(EdgeWeightFormat in)
	{
		std::string output;
		switch (in)
		{
		case EdgeWeightFormat::notSet:
			output = "NOT_SET";
			break;
		case EdgeWeightFormat::function:
			output = "FUNCTION";
			break;
		case EdgeWeightFormat::fullMatrix:
			output = "FULL_MATRIX";
			break;
		case EdgeWeightFormat::upperRow:
			output = "UPPER_ROW";
			break;
		case EdgeWeightFormat::lowerRow:
			output = "LOWER_ROW";
			break;
		case EdgeWeightFormat::upperDiagRow:
			output = "UPPER_DIAG_ROW";
			break;
		case EdgeWeightFormat::lowerDiagRow:
			output = "LOWER_DIAG_ROW";
			break;
		case EdgeWeightFormat::upperCol:
			output = "UPPER_COL";
			break;
		case EdgeWeightFormat::lowerCol:
			output = "LOWER_COL";
			break;
		case EdgeWeightFormat::upperDiagCol:
			output = "UPPER_DIAG_COL";
			break;
		case EdgeWeightFormat::lowerDiagCol:
			output = "LOWER_DIAG_COL";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}

	std::string toString(Type in)
	{
		std::string output;
		switch (in)
		{
		case Type::notSet:
			output = "NOT_SET";
			break;
		case Type::tsp:
			output = "TSP";
			break;
		case Type::atsp:
			output = "ATSP";
			break;
		case Type::sop:
			output = "SOP";
			break;
		case Type::hcp:
			output = "HCP";
			break;
		case Type::cvrp:
			output = "CVRP";
			break;
		case Type::tour:
			output = "TOUR";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}

	std::string toString(NodeCoordType in)
	{
		std::string output;
		switch (in)
		{
		case NodeCoordType::notSet:
			output = "NOT_SET";
			break;
		case NodeCoordType::twodCoords:
			output = "TWOD_COORDS";
			break;
		case NodeCoordType::threedCoords:
			output = "THREED_COORDS";
			break;
		case NodeCoordType::noCoords:
			output = "NO_COORDS";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}

	std::string toString(DisplayDataType in)
	{
		std::string output;
		switch (in)
		{
		case DisplayDataType::notSet:
			output = "NOT_SET";
			break;
		case DisplayDataType::coordDisplay:
			output = "COORD_DISPLAY";
			break;
		case DisplayDataType::twodDisplay:
			output = "TWOD_DISPLAY";
			break;
		case DisplayDataType::noDisplay:
			output = "NO_DISPLAY";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}

	std::string toString(EdgeDataFormat in)
	{
		std::string output;
		switch (in)
		{
		case  EdgeDataFormat::notSet:
			output = "NOT_SET";
			break;
		case  EdgeDataFormat::edgeList:
			output = "EDGE_LIST";
			break;
		case  EdgeDataFormat::adjList:
			output = "ADJ_LIST";
			break;
		default:
			throw std::invalid_argument("Unsupported enum extension");
		}
		return output;
	}
}