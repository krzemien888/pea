#include "stdafx.h"
#include "matrixGraph.h"
	

matrixGraph matrixGraph::generate(const int vertexCount, const int density, const int minValue, const int maxValue)
{
	return matrixGraph();
}

void matrixGraph::setMatrix(std::vector<std::vector<int>>& matrix)
{
	_matrix = matrix;
}

void matrixGraph::setConnection(const int from, const int to, const int value)
{
	_matrix[from][to] = value;
}

void matrixGraph::addVertex()
{
	for (auto line : _matrix)
		line.push_back(0);
	
	std::vector<int> v(_matrix.size() + 1, 0);

	_matrix.push_back(v);
}

int matrixGraph::getConnectionValue(const int from, const int to) const
{
	return _matrix[from][to];
}

std::vector<int> matrixGraph::getNeighbours(const int vectex) const
{
	return _matrix[vectex];
}

size_t matrixGraph::getSize() const
{
	return _matrix.size();
}

bool matrixGraph::operator==(const matrixGraph & arg)
{
	if (getSize() != arg.getSize())
		return false;
	
	for (size_t x = 0; x < getSize(); x++)
		for (size_t y = 0; y < getSize(); y++)
			if (getConnectionValue(x, y) != arg.getConnectionValue(x, y))
				return false;

	return true;
}
