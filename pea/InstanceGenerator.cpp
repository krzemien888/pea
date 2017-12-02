#include "stdafx.h"
#include "InstanceGenerator.h"
#include "matrixGraph.h"
#include "TSPHeader.h"
#include "TSPEnums.h"

void InstanceGenerator::generate()
{
	using namespace std;

	char symmetric;
	int lowBound, highBound;

	getParameters(symmetric, lowBound, highBound);
	for (int i = lowBound; i <= highBound; i++)
	{
		matrixGraph graph = matrixGraph::generate(i, symmetric=='t', 1,500);
		TSPHeader header = getHeader(i, symmetric == 't');
		writeToFile(graph, header);
	}
	system("pause");
}

TSPHeader InstanceGenerator::getHeader(int size, bool isSymmetric)
{
	TSPHeader header;
	std::stringstream ss;
	ss << "generated" << size;
	if (isSymmetric)
	{
		ss << ".tsp";
		header.setType(TSP::Type::tsp);
	}
	else
	{
		ss << ".atsp";
		header.setType(TSP::Type::atsp);
	}
	header.setName(ss.str());
	header.setComment("generatedFromCode");
	header.setDimension(size);
	header.setWeightType(TSP::WeightType::explicitType);
	header.setWeightFormat(TSP::EdgeWeightFormat::fullMatrix);

	return header;
}

void InstanceGenerator::writeToFile(matrixGraph & graph, TSPHeader & header)
{
	using namespace std;

	ofstream file(header.getName(), ios::trunc);

	cout << "Writing file: " << header.getName() << endl;
	if (file.is_open())
	{
		file << header;
		file << "EDGE_WEIGHT_SECTION" << endl;
		file << graph;
		file << "EOF";

		file.close();
		cout << "Success!" << endl;
	}
	else
		cout << "Failure!" << endl;

}

void InstanceGenerator::getParameters(char & symmetric, int & lowBound, int & highBound)
{
	using namespace std;
	system("cls");
	cout << "\nMinimalna instancja: ";
	cin >> lowBound;
	cout << "\nMaksymalna instancja: ";
	cin >> highBound;
	cout << "\nSymmetric? [t/n]: ";
	cin >> symmetric;
	cout << endl;
	system("cls");
}
