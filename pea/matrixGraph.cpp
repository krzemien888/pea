#include "stdafx.h"
#include "matrixGraph.h"
	

matrixGraph matrixGraph::generate(const int vertexCount, const float density, const int minValue, const int maxValue)
{
	matrixGraph m;
	while (m.getSize() != vertexCount)
		m.addVertex();

	while (m.getDensity() != density)
		m.setConnection(rand() % vertexCount, rand() % vertexCount, rand() % maxValue + minValue);

	return m;
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
	if (isEmpty())
	{
		std::vector<int> v(1, 0);
		_matrix.push_back(v);
		return;
	}
	else
	{
		for (std::vector<int>& line : _matrix)
			line.push_back(0);
	
		std::vector<int> v(_matrix.size() + 1, 0);

		_matrix.push_back(v);
	}
}

int matrixGraph::getConnectionValue(const int from, const int to) const
{
	return _matrix[from][to];
}

std::vector<int> matrixGraph::getNeighbours(const int vectex) const
{
	return _matrix[vectex];
}

float matrixGraph::getDensity() const
{
	int edgeCount = 0;

	for (auto row : _matrix)
		for (auto edge : row)
			if (edge != 0)
				edgeCount++;

	float density = (float)edgeCount/(float)(getSize() * (getSize() - 1));

	return density;
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

bool matrixGraph::isEmpty() const
{
	return _matrix.size() == 0;
}

std::ostream & operator<<(std::ostream & stream, const matrixGraph & m)
{
	for (unsigned int x = 0; x < m.getSize(); x++)
	{
		for (unsigned int y = 0; y < m.getSize(); y++)
			stream << m.getConnectionValue(x, y) << " ";
		stream << std::endl;
	}	
	return stream;
}
