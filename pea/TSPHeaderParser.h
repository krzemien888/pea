#pragma once

#include "TSPHeader.h"
#include "stdafx.h"

class TSPHeaderParser
{
public:
	TSPHeaderParser();
	~TSPHeaderParser() = default;

	TSPHeader parse(std::vector<std::string> text);
	TSPHeader parse(std::string text);

private:

	void initMaps();

	void initSetFunctionMap();
	void initTypeMap();
	void initWeightTypeMap();
	void initEdgeWeightFormatMap();
	void initEdgeDataFormatMap();
	void initNodeCoordTypeMap();
	void initDisplayDataTypeMap();

	void setName(TSPHeader& header, std::string &value) const;
	void setType(TSPHeader& header, std::string &value) const;
	void setComment(TSPHeader& header, std::string &value) const;
	void setDimension(TSPHeader& header, std::string &value) const;
	void setCapacity(TSPHeader& header, std::string &value) const;
	void setEdgeWeightType(TSPHeader& header, std::string &value) const;
	void setEdgeWeightFormat(TSPHeader& header, std::string &value) const;
	void setEdgeDataFormat(TSPHeader& header, std::string &value) const;
	void setNodeCoordType(TSPHeader& header, std::string &value) const;
	void setDisplayDataType(TSPHeader& header, std::string &value) const;

	void eraseSpaces(std::string &s);
	void splitSettingValueString(std::string &input, std::string &setting, std::string &value);
	
	std::unordered_map<std::string, std::function<void(TSPHeaderParser&, TSPHeader&, std::string&)>> setFunctionMap;
	std::unordered_map<std::string, TSP::Type> typeMap;
	std::unordered_map<std::string, TSP::WeightType> weightTypeMap;
	std::unordered_map<std::string, TSP::EdgeWeightFormat> edgeWeightFormatMap;
	std::unordered_map<std::string, TSP::EdgeDataFormat> edgeDataFormatMap;
	std::unordered_map<std::string, TSP::NodeCoordType> nodeCoordTypeMap;
	std::unordered_map<std::string, TSP::DisplayDataType> displayDataTypeMap;
};

