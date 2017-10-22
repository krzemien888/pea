#include "stdafx.h"
#include "TSPHeader.h"


std::string TSPHeader::getName() const
{
	return name;
}

void TSPHeader::setName(std::string newName)
{
	name = newName;
}

TSP::Type TSPHeader::getType() const
{
	return type;
}

void TSPHeader::setType(TSP::Type newType)
{
	type = newType;
}

std::string TSPHeader::getComment() const
{
	return comment;
}

void TSPHeader::setComment(std::string newComment)
{
	comment = newComment;
}

int TSPHeader::getDimension() const
{
	return dimension;
}

void TSPHeader::setDimension(int newDimension)
{
	dimension = newDimension;
}

int TSPHeader::getCapacity() const
{
	return capacity;
}

void TSPHeader::setCapacity(int newCapacity)
{
	capacity = newCapacity;
}

TSP::WeightType TSPHeader::getWeightType() const
{
	return weightType;
}

void TSPHeader::setWeightType(TSP::WeightType newType)
{
	weightType = newType;
}

TSP::EdgeWeightFormat TSPHeader::getEdgeWeightFormat() const
{
	return edgeWeightFormat;
}

void TSPHeader::setWeightFormat(TSP::EdgeWeightFormat newWeight)
{
	edgeWeightFormat = newWeight;
}

TSP::EdgeDataFormat TSPHeader::getEdgeDataFormat() const
{
	return edgeDataFormat;
}

void TSPHeader::setEdgeDataFormat(TSP::EdgeDataFormat newFormat)
{
	edgeDataFormat = newFormat;
}

TSP::NodeCoordType TSPHeader::getNodeCoordType() const
{
	return nodeCoordType;
}

void TSPHeader::setNodeCoordType(TSP::NodeCoordType newCoordType)
{
	nodeCoordType = newCoordType;
}

TSP::DisplayDataType TSPHeader::getDisplayDataType() const
{
	return displayDataType;;
}

void TSPHeader::setDisplayDataType(TSP::DisplayDataType newDataType)
{
	displayDataType = newDataType;
}
