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
	distFuncMap[TSP::WeightType::geo] = &TSPDataParser::calcEucl;
	distFuncMap[TSP::WeightType::explicitType] = &TSPDataParser::calcMatrix;
}

void TSPDataParser::initEdgeReadMap()
{
	edgeReadMap[TSP::EdgeWeightFormat::function] = &TSPDataParser::readCoord;
	edgeReadMap[TSP::EdgeWeightFormat::notSet] = &TSPDataParser::readCoord;
	edgeReadMap[TSP::EdgeWeightFormat::fullMatrix] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::upperRow] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::upperDiagRow] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::upperCol] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::upperDiagCol] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::lowerRow] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::lowerDiagRow] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::lowerCol] = &TSPDataParser::readMatrix;
	edgeReadMap[TSP::EdgeWeightFormat::lowerDiagCol] = &TSPDataParser::readMatrix;

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
	
	float coord;
	while (ss >> coord)
		coords.push_back((int)coord);


	if (coords.size() != 2 || index == 9)
	{
		index++;
		index--;

	}

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
	std::stringstream ss(line);
	
	int tmp;
	while (ss >> tmp)
		rawVector.push_back(tmp);
}

void TSPDataParser::calcMatrix()
{
	resultGraph.addVertex(header.getDimension());
	switch (header.getEdgeWeightFormat()) {
	case TSP::EdgeWeightFormat::fullMatrix: {
		for (int i = 0; i < header.getDimension(); ++i) {
			for (int j = 0; j < header.getDimension(); ++j) {
				resultGraph.setConnection(i, j, rawVector[i * header.getDimension() + j]);
			}
		}
		break;
	}
	case TSP::EdgeWeightFormat::upperRow:
	case TSP::EdgeWeightFormat::upperDiagRow:
	case TSP::EdgeWeightFormat::upperCol:
	case TSP::EdgeWeightFormat::upperDiagCol: {
		for (int i = 0; i < header.getDimension(); ++i) {
			for (int j = header.getEdgeWeightFormat() == TSP::EdgeWeightFormat::upperDiagRow ? i : i + 1; j < header.getDimension(); ++j)
			{
				int col = header.getEdgeWeightFormat() == TSP::EdgeWeightFormat::upperDiagRow ? j : j - i - 1;
				double weight = rawVector[i * header.getDimension() + col - i * (i + 1) / 2];
				resultGraph.setConnection(i, j, (int)weight);
				resultGraph.setConnection(j, i, (int)weight);
			}
		}
		break;
	}
	case TSP::EdgeWeightFormat::lowerRow:
	case TSP::EdgeWeightFormat::lowerDiagRow:
	case TSP::EdgeWeightFormat::lowerCol:
	case TSP::EdgeWeightFormat::lowerDiagCol:
	{
		for (int i = 0; i < header.getDimension(); ++i)
		{
			int cols = header.getEdgeWeightFormat() == TSP::EdgeWeightFormat::lowerDiagRow ? i : i - 1;
			for (int j = 0; j <= cols; ++j)
			{
				int row = header.getEdgeWeightFormat() == TSP::EdgeWeightFormat::lowerDiagRow ? i : i - 1;
				double weight = rawVector[row * header.getDimension() + j - (row * header.getDimension() - row * (row + 1) / 2)];
				resultGraph.setConnection(i, j, (int)weight);
				resultGraph.setConnection(j, i, (int)weight);
			}
		}
		break;
	}
	default:
		throw std::runtime_error("Parse error");
	}
}
