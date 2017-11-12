#include <gtest\gtest.h>
#include "stdafx.h"


TEST(TSPFileReaderTest, ReaderShouldReturnProperMatrixGraphTSP)
{
	TSPFileReader reader;
	std::string filename = "tmpFile.tsp";

	std::ofstream tmpFile(filename, std::ios::out | std::ios::trunc);


	tmpFile << "NAME: berlin52\n";
	tmpFile << "TYPE : TSP\n";
	tmpFile << "COMMENT : 52 locations in Berlin(Groetschel)\n";
	tmpFile << "DIMENSION : 3\n";
	tmpFile << "EDGE_WEIGHT_TYPE : EUC_2D\n";
	tmpFile << "NODE_COORD_SECTION\n";
	tmpFile << "1 0 0\n";
	tmpFile << "2 1 0\n";
	tmpFile << "3 0 1\n";
	tmpFile << "EOF";

	tmpFile.close();
	

	std::vector<std::vector<int>> graphMatrix = { { 0, 1, 1}, {1, 0, 1},{1,1,0} };
	matrixGraph graph;
	graph.setMatrix(graphMatrix);

	reader.setFileName("tmpFile.tsp");
	reader.tryParse();
	auto parsedGraph = reader.getData();

	ASSERT_EQ(parsedGraph, graph);

	remove("tmpFile.tsp");
}

TEST(TSPFileReaderTests, ReaderShouldCheckIfFileExists)
{
	TSPFileReader reader;
	ASSERT_ANY_THROW(reader.setFileName("nonExistingFile.tsp"));
}

TEST(TSPFileReaderTests, ParserShouldProperlyDetectKindOfLine)
{
	std::ifstream file("berlin52.tsp", std::ifstream::in);
	TSPFileReader reader;

	std::vector<std::string> headerText, dataText;
	std::string line;

	if (file.is_open() && file.good())
	{
		TSPHeaderParser headerParser;

		while (getline(file, line))
		{
			if (reader.isHeaderLine(line))
				headerText.push_back(line);
			else if (reader.isDataLine(line))
				dataText.push_back(line);
			else if (reader.isSectionLine(line))
				continue;
		}
	}
	else
	{
		FAIL() << "Test file berlin52.tsp couln't be open.";
	}

	file.close();

	ASSERT_EQ(headerText.size(), 5);
	ASSERT_EQ(dataText.size(), 52);
}