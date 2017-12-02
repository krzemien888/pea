#include "stdafx.h"
#include "DynamicAlgorithm.h"



Result DynamicAlgorithm::apply(matrixGraph * graph)
{
	std::vector<int> outputPath;
	npow = (long long int)pow(2, graph->getSize());;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	valueVector.clear();
	pathVector.clear();

	valueVector.resize(graph->getSize());
	pathVector.resize(graph->getSize());

	try {
		for (auto &v : valueVector)
			v.resize(npow, -1);
		for (auto &v : pathVector)
			v.resize(npow, -1);
	}
	catch (std::exception &e)
	{
		std::cout << "Blad podczas alokowania pamieci\n";
		std::cout << "vector max: " << valueVector.max_size() << "\n";
		std::cout << "Given: " << npow << '\n';
		std::cout << e.what() << '\n';
		throw e;
		system("pause");
	}

	startTime = std::chrono::high_resolution_clock::now();

	for (long long int i = 0; i < (long long int)graph->getSize(); i++)
		setValue(i, 0, graph->getConnectionValue(i, 0));

	int result = getCost(0, npow - 2, graph);
	outputPath.push_back(0);
	getPath(0, npow - 2, outputPath);

	endTime = std::chrono::high_resolution_clock::now();

	Result output;
	output.fileName = graph->getName();
	output.path = outputPath;
	output.result = result;
	output.time = (int)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

	return output;
}

int DynamicAlgorithm::getCost(int start, long long int set, matrixGraph* graph)
{
	long long int masked;
	long long int mask;
	int result = -1;
	int temp;

	if (getValue(start, set) != -1)
		return getValue(start, set);
	else
	{
		for (int x = 0; x < (int)graph->getSize(); x++)
		{
			mask = npow - 1 - (long long int)pow(2, x);
			masked = set&mask;
			if (masked != set)
			{
				temp = graph->getConnectionValue(start, x) + getCost(x, masked, graph);
				if (result == -1 || result > temp)
				{
					result = temp;
					setPathValue(start, set, x);
				}
			}
		}
		setValue(start, set, result);
		return result;
	}
}

void DynamicAlgorithm::getPath(int start, long long int set, std::vector<int> &output)
{
	if (getPathValue(start, set) == -1)
		return;

	int x = getPathValue(start, set);
	long long int mask = npow - 1 - (long long int)pow(2, x);
	long long int masked = set&mask;
	output.push_back(x);
	getPath(x, masked, output);
}

int DynamicAlgorithm::getValue(long long int x, long long int y)
{
	return valueVector[x][y];
}

int DynamicAlgorithm::getPathValue(long long int x, long long int y)
{
	return pathVector[x][y];
}

void DynamicAlgorithm::setValue(long long int x, long long int y, int value)
{
	valueVector[x][y] = value;
}

void DynamicAlgorithm::setPathValue(long long int x, long long int y, int value)
{
	pathVector[x][y] = value;
}
