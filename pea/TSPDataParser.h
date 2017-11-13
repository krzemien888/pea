#pragma once

#include "stdafx.h"

#include "matrixGraph.h"
#include "TSPHeader.h"

class TSPDataParser
{
public:
	TSPDataParser(TSPHeader h) : header(h) { initMaps(); };
	~TSPDataParser() = default;

	void parse(std::vector<std::string> text);
	matrixGraph getGraph();


private:
	TSPHeader header;
	matrixGraph resultGraph;
	std::vector<std::vector<int>> rawData;
	std::vector<int> rawVector;

	void initMaps();
	void initDistFuncMap();
	void initEdgeReadMap();

	void calcEucl();
	void calcMatrix();
	
	void readCoord(std::string& line);
	void readMatrix(std::string &line);

	std::unordered_map<TSP::WeightType, std::function<void(TSPDataParser&)>> distFuncMap;
	std::unordered_map<TSP::EdgeWeightFormat, std::function<void(TSPDataParser&, std::string&)>> edgeReadMap;
};

