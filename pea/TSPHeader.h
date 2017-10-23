#pragma once

#include "stdafx.h"

class TSPHeader final
{
public:
	TSPHeader() = default;
	~TSPHeader() = default;

	std::string getName() const;
	void setName(std::string newName);

	TSP::Type getType() const;
	void setType(TSP::Type newType);

	std::string getComment() const;
	void setComment(std::string newComment);

	int getDimension() const;
	void setDimension(int newDimension);

	int getCapacity() const;
	void setCapacity(int newCapacity);

	TSP::WeightType getWeightType() const;
	void setWeightType(TSP::WeightType newType);

	TSP::EdgeWeightFormat getEdgeWeightFormat() const;
	void setWeightFormat(TSP::EdgeWeightFormat newWeight);

	TSP::EdgeDataFormat getEdgeDataFormat() const;
	void setEdgeDataFormat(TSP::EdgeDataFormat newFormat);

	TSP::NodeCoordType getNodeCoordType() const;
	void setNodeCoordType(TSP::NodeCoordType newCoordType);

	TSP::DisplayDataType getDisplayDataType() const;
	void setDisplayDataType(TSP::DisplayDataType newDataType);

private:
	std::string name;
	TSP::Type type = TSP::Type::notSet;
	std::string comment;
	int dimension = -1;
	int capacity = -1;
	TSP::WeightType weightType = TSP::WeightType::notSet;
	TSP::EdgeWeightFormat edgeWeightFormat = TSP::EdgeWeightFormat::notSet;
	TSP::EdgeDataFormat edgeDataFormat = TSP::EdgeDataFormat::notSet;
	TSP::NodeCoordType nodeCoordType = TSP::NodeCoordType::notSet;
	TSP::DisplayDataType displayDataType = TSP::DisplayDataType::notSet;
};

