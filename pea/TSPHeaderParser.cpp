#include "stdafx.h"
#include "TSPHeaderParser.h"
#include "TSPHeader.h"

using namespace TSP;

TSPHeaderParser::TSPHeaderParser()
{
	initMaps();
}

TSPHeader TSPHeaderParser::parse(std::vector<std::string> text)
{
	TSPHeader output;
	
	std::string setting, value;
	for(auto line : text)
	{
		splitSettingValueString(line, setting, value);
		
		auto find = setFunctionMap.find(setting);

		if (find != setFunctionMap.end())
			find->second(*this, output, value);
		else
			throw std::invalid_argument("Parse error: unrecognised setting");
	}

	return output;
}

TSPHeader TSPHeaderParser::parse(std::string text)
{
	std::vector<std::string> s = { text };
	return parse(s);
}

void TSPHeaderParser::initMaps()
{
	initSetFunctionMap();
	initTypeMap();
	initWeightTypeMap();
	initEdgeWeightFormatMap();
	initEdgeDataFormatMap();
	initNodeCoordTypeMap();
	initDisplayDataTypeMap();
}

void TSPHeaderParser::initSetFunctionMap()
{
	setFunctionMap["NAME"] = &TSPHeaderParser::setName;
	setFunctionMap["TYPE"] = &TSPHeaderParser::setType;
	setFunctionMap["COMMENT"] = &TSPHeaderParser::setComment;
	setFunctionMap["DIMENSION"] = &TSPHeaderParser::setDimension;
	setFunctionMap["CAPACITY"] = &TSPHeaderParser::setCapacity;
	setFunctionMap["EDGE_WEIGHT_TYPE"] = &TSPHeaderParser::setEdgeWeightType;
	setFunctionMap["EDGE_WEIGHT_FORMAT"] = &TSPHeaderParser::setEdgeWeightFormat;
	setFunctionMap["EDGE_DATA_FORMAT"] = &TSPHeaderParser::setEdgeDataFormat;
	setFunctionMap["NODE_COORD_TYPE"] = &TSPHeaderParser::setNodeCoordType;
	setFunctionMap["DISPLAY_DATA_TYPE"] = &TSPHeaderParser::setDisplayDataType;
}

void TSPHeaderParser::initTypeMap()
{
	typeMap["ATSP"] = TSP::Type::atsp;
	typeMap["TSP"] = TSP::Type::tsp;
	typeMap["SOP"] = TSP::Type::sop;
	typeMap["HCP"] = TSP::Type::hcp;
	typeMap["CVRP"] = TSP::Type::cvrp;
	typeMap["TOUR"] = TSP::Type::tour;
}

void TSPHeaderParser::initWeightTypeMap()
{
	weightTypeMap["EXPLICIT"] = TSP::WeightType::explicitType;
	weightTypeMap["EUC_2D"] = TSP::WeightType::euclidean2d;
	weightTypeMap["EUC_3D"] = TSP::WeightType::euclidean3d;
	weightTypeMap["MAX_2D"] = TSP::WeightType::max2d;
	weightTypeMap["MAX_3D"] = TSP::WeightType::max3d;
	weightTypeMap["MAN_2D"] = TSP::WeightType::man2d;
	weightTypeMap["MAN_3D"] = TSP::WeightType::man3d;
	weightTypeMap["CEIL_2D"] = TSP::WeightType::ceil2d;
	weightTypeMap["GEO"] = TSP::WeightType::geo;
	weightTypeMap["ATT"] = TSP::WeightType::att;
	weightTypeMap["XRAY1"] = TSP::WeightType::xray1;
	weightTypeMap["XRAY2"] = TSP::WeightType::xray2;
	weightTypeMap["SPECIAL"] = TSP::WeightType::special;
}

void TSPHeaderParser::initEdgeWeightFormatMap()
{
	edgeWeightFormatMap["FUNCTION"] = TSP::EdgeWeightFormat::function;
	edgeWeightFormatMap["FULL_MATRIX"] = TSP::EdgeWeightFormat::fullMatrix;
	edgeWeightFormatMap["UPPER_ROW"] = TSP::EdgeWeightFormat::upperRow;
	edgeWeightFormatMap["LOWER_ROW"] = TSP::EdgeWeightFormat::lowerRow;
	edgeWeightFormatMap["UPPER_DIAG_ROW"] = TSP::EdgeWeightFormat::upperDiagRow;
	edgeWeightFormatMap["LOWER_DIAG_ROW"] = TSP::EdgeWeightFormat::lowerDiagRow;
	edgeWeightFormatMap["UPPER_COL"] = TSP::EdgeWeightFormat::upperCol;
	edgeWeightFormatMap["LOWER_COL"] = TSP::EdgeWeightFormat::lowerCol;
	edgeWeightFormatMap["UPPER_DIAG_COL"] = TSP::EdgeWeightFormat::upperDiagCol;
	edgeWeightFormatMap["LOWER_DIAG_COL"] = TSP::EdgeWeightFormat::lowerDiagCol;
}

void TSPHeaderParser::initEdgeDataFormatMap()
{
	edgeDataFormatMap["EDGE_LIST"] = TSP::EdgeDataFormat::edgeList;
	edgeDataFormatMap["ADJ_LIST"] = TSP::EdgeDataFormat::adjList;
}

void TSPHeaderParser::initNodeCoordTypeMap()
{
	nodeCoordTypeMap["TWOD_COORDS"] = TSP::NodeCoordType::twodCoords;
	nodeCoordTypeMap["THREED_COORDS"] = TSP::NodeCoordType::threedCoords;
	nodeCoordTypeMap["NO_COORDS"] = TSP::NodeCoordType::noCoords;
}

void TSPHeaderParser::initDisplayDataTypeMap()
{
	displayDataTypeMap["COORD_DISPLAY"] = TSP::DisplayDataType::coordDisplay;
	displayDataTypeMap["TWOD_DISPLAY"] = TSP::DisplayDataType::twodDisplay;
	displayDataTypeMap["NO_DISPLAY"] = TSP::DisplayDataType::noDisplay;
}

void TSPHeaderParser::setName(TSPHeader & header, std::string & value) const
{
	header.setName(value);
}

void TSPHeaderParser::setType(TSPHeader & header, std::string & value) const
{
	auto found = typeMap.find(value);
	if (found == typeMap.end())
		throw std::invalid_argument("Parse error: Invalid type value");
	else
		header.setType(found->second);
}

void TSPHeaderParser::setComment(TSPHeader & header, std::string & value) const
{
	header.setComment(value);
}

void TSPHeaderParser::setDimension(TSPHeader & header, std::string & value) const
{
	try {
		header.setDimension(stoi(value));
	}
	catch (std::invalid_argument)
	{
		throw std::invalid_argument("Parse error: invalid dimension value");
	}
}

void TSPHeaderParser::setCapacity(TSPHeader & header, std::string & value) const
{
	try {
		header.setCapacity(stoi(value));
	}
	catch (std::invalid_argument)
	{
		throw std::invalid_argument("Parse error: invalid capacity value");
	}
}

void TSPHeaderParser::setEdgeWeightType(TSPHeader & header, std::string & value) const
{
	auto found = weightTypeMap.find(value);
	if (found == weightTypeMap.end())
		throw std::invalid_argument("Parse error: Invalid weight type value");
	else
		header.setWeightType(found->second);

}

void TSPHeaderParser::setEdgeWeightFormat(TSPHeader & header, std::string & value) const
{
	auto found = edgeWeightFormatMap.find(value);
	if (found == edgeWeightFormatMap.end())
		throw std::invalid_argument("Parse error: Invalid weight format value");
	else
		header.setWeightFormat(found->second);
}

void TSPHeaderParser::setEdgeDataFormat(TSPHeader & header, std::string & value) const
{
	auto found = edgeDataFormatMap.find(value);
	if (found == edgeDataFormatMap.end())
		throw std::invalid_argument("Parse error: Invalid data format value");
	else
		header.setEdgeDataFormat(found->second);
}

void TSPHeaderParser::setNodeCoordType(TSPHeader & header, std::string & value) const
{
	auto found = nodeCoordTypeMap.find(value);
	if (found == nodeCoordTypeMap.end())
		throw std::invalid_argument("Parse error: Invalid node coord type value");
	else
		header.setNodeCoordType(found->second);
}

void TSPHeaderParser::setDisplayDataType(TSPHeader & header, std::string & value) const
{
	auto found = displayDataTypeMap.find(value);
	if (found == displayDataTypeMap.end())
		throw std::invalid_argument("Parse error: Invalid display data type value");
	else
		header.setDisplayDataType(found->second);
}

void TSPHeaderParser::eraseSpaces(std::string & s)
{
	while (s.find(' ') != std::string::npos)
		s.erase(s.find(' '), 1);
}

void TSPHeaderParser::splitSettingValueString(std::string & input, std::string & setting, std::string & value)
{
	eraseSpaces(input);
	size_t delimeter = input.find(':');
	setting = input.substr(0, delimeter);
	value = input.substr(delimeter + 1, input.size());
}
