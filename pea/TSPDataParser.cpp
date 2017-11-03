#include "stdafx.h"
#include "TSPDataParser.h"
#include "TSPEnums.h"

void TSPDataParser::parse(std::vector<std::string> text)
{
	for(auto line : text)
	{
		auto foundReader = edgeReadMap.find(header.getEdgeWeightFormat());

		if (foundReader == edgeReadMap.end())
			throw std::invalid_argument("Data parser error: Couldnt found function to parse");
		else
			foundReader->second(*this, line);
	}

	auto foundCalc = distFuncMap.find(header.getWeightType());

	if (foundCalc == distFuncMap.end())
		throw std::invalid_argument("Data parser error: Couldnt found function to calculate distance");
	else
		foundCalc->second(*this);

	
}

matrixGraph TSPDataParser::getGraph()
{
	return resultGraph;
}

void TSPDataParser::initMaps()
{
	initDistFuncMap();
	initEdgeReadMap();
}

void TSPDataParser::initDistFuncMap()
{
	distFuncMap[TSP::WeightType::euclidean2d] = &TSPDataParser::calcEucl;
	distFuncMap[TSP::WeightType::euclidean3d] = &TSPDataParser::calcEucl;
}

void TSPDataParser::initEdgeReadMap()
{
	edgeReadMap[TSP::EdgeWeightFormat::function] = &TSPDataParser::readCoord;
	edgeReadMap[TSP::EdgeWeightFormat::notSet] = &TSPDataParser::readCoord;
	edgeReadMap[TSP::EdgeWeightFormat::fullMatrix] = &TSPDataParser::readMatrix;
}

void TSPDataParser::calcEucl()
{
	for (unsigned int distFrom = 0; distFrom < rawData.size(); distFrom++)
	{
		for (unsigned int distTo = 0; distTo < rawData.size(); distTo++)
		{
			if (rawData[distFrom].size() != rawData[distTo].size())
				throw std::logic_error("Calculation impossible: Points from different dimensions");
			int result = 0;
			for (unsigned int coord = 0; coord < rawData[distFrom].size(); coord++)
				result += (int)pow(rawData[distFrom][coord] - rawData[distTo][coord], 2);
			result = (int)round(sqrt(result));
			resultGraph.setConnection(distFrom, distTo, result);
		}
	}
	
}

void TSPDataParser::readCoord(std::string & line)
{
	std::stringstream ss(line);

	unsigned int index;
	std::vector<int> coords;
	ss >> index;
	index--;
	
	rawData.resize(header.getDimension());
	
	int coord;
	while (ss >> coord)
		coords.push_back(coord);

	rawData[index] = coords;



	
	if (header.getDimension() != -1)
	{
		if(resultGraph.getSize() != header.getDimension())
			resultGraph.addVertex(header.getDimension());
	}
	else
	{
		if(resultGraph.getSize() != (unsigned int)pow(rawData.size(), 2))
			resultGraph.addVertex((unsigned int)pow(rawData.size(), 2));
	}
}

void TSPDataParser::readMatrix(std::string & line)
{
	throw std::logic_error("TSPDataParser::readMatrix: Not implemented yet");
}
