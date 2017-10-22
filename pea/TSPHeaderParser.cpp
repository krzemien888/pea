#include "stdafx.h"
#include "TSPHeaderParser.h"
#include "TSPHeader.h"

using namespace TSP;

TSPHeaderParser::TSPHeaderParser()
{
	initMaps();
}

TSPHeader TSPHeaderParser::parse(std::string header)
{
	TSPHeader output;
	
	std::stringstream ss(header);
	
	std::string line, setting, value;
	while (getline(ss, line))
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
	typeMap["ATSP"] = atsp;
	typeMap["TSP"] = tsp;
	typeMap["SOP"] = sop;
	typeMap["HCP"] = hcp;
	typeMap["CVRP"] = cvrp;
	typeMap["TOUR"] = tour;
}

void TSPHeaderParser::initWeightTypeMap()
{
	weightTypeMap["EXPLICIT"] = explicitType;
	weightTypeMap["EUC_2D"] = euclidean2d;
	weightTypeMap["EUC_3D"] = euclidean3d;
	weightTypeMap["MAX_2D"] = max2d;
	weightTypeMap["MAX_3D"] = max3d;
	weightTypeMap["MAN_2D"] = man2d;
	weightTypeMap["MAN_3D"] = man3d;
	weightTypeMap["CEIL_2D"] = ceil2d;
	weightTypeMap["GEO"] = geo;
	weightTypeMap["ATT"] = att;
	weightTypeMap["XRAY1"] = xray1;
	weightTypeMap["XRAY2"] = xray2;
	weightTypeMap["SPECIAL"] = special;
}

void TSPHeaderParser::initEdgeWeightFormatMap()
{
	edgeWeightFormatMap["FUNCTION"] = function;
	edgeWeightFormatMap["FULL_MATRIX"] = fullMatrix;
	edgeWeightFormatMap["UPPER_ROW"] = upperRow;
	edgeWeightFormatMap["LOWER_ROW"] = lowerRow;
	edgeWeightFormatMap["UPPER_DIAG_ROW"] = upperDiagRow;
	edgeWeightFormatMap["LOWER_DIAG_ROW"] = lowerDiagRow;
	edgeWeightFormatMap["UPPER_COL"] = upperCol;
	edgeWeightFormatMap["LOWER_COL"] = lowerCol;
	edgeWeightFormatMap["UPPER_DIAG_COL"] = upperDiagCol;
	edgeWeightFormatMap["LOWER_DIAG_COL"] = lowerDiagCol;
}

void TSPHeaderParser::initEdgeDataFormatMap()
{
	edgeDataFormatMap["EDGE_LIST"] = edgeList;
	edgeDataFormatMap["ADJ_LIST"] = adjList;
}

void TSPHeaderParser::initNodeCoordTypeMap()
{
	nodeCoordTypeMap["TWOD_COORDS"] = twodCoords;
	nodeCoordTypeMap["THREED_COORDS"] = threedCoords;
	nodeCoordTypeMap["NO_COORDS"] = noCoords;
}

void TSPHeaderParser::initDisplayDataTypeMap()
{
	displayDataTypeMap["COORDS_DISPLAY"] = coordDisplay;
	displayDataTypeMap["TWOD_DISPLAY"] = twodDisplay;
	displayDataTypeMap["NO_DISPLAY"] = noDisplay;
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
		throw std::invalid_argument("Parse error: Invalid data format value");
	else
		header.setNodeCoordType(found->second);
}

void TSPHeaderParser::setDisplayDataType(TSPHeader & header, std::string & value) const
{
	auto found = displayDataTypeMap.find(value);
	if (found == displayDataTypeMap.end())
		throw std::invalid_argument("Parse error: Invalid data format value");
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
	int delimeter = input.find(':');
	setting = input.substr(0, delimeter);
	value = input.substr(delimeter + 1, input.size());
}
