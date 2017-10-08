#pragma once

#include "stdafx.h"

class matrixGraph
{
public:

	static matrixGraph generate(const int vertexCount, const int density, const int minValue = 1, const int maxValue = 20);

	matrixGraph() = default;
	~matrixGraph() = default;

	void setMatrix(std::vector<std::vector<int>> &matrix);
	void setConnection(const int from, const int to, const int value);
	void addVertex();

	int getConnectionValue(const int from, const int to) const;
	std::vector<int> getNeighbours(const int vectex) const; 
	size_t getSize() const ;


	bool operator==(const matrixGraph& arg);

private:
	std::vector<std::vector<int>> _matrix;
};

