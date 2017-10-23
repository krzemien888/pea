#pragma once

#include "stdafx.h"

class matrixGraph
{
public:

	static matrixGraph generate(const int vertexCount, const float density, const int minValue = 1, const int maxValue = 20);

	matrixGraph() = default;
	~matrixGraph() = default;

	void setMatrix(std::vector<std::vector<int>> &matrix);
	void setConnection(const int from, const int to, const int value);
	void addVertex();
	void addVertex(unsigned int newSize);

	int getConnectionValue(const int from, const int to) const;
	std::vector<int> getNeighbours(const int vectex) const; 
	float getDensity() const;
	size_t getSize() const ;


	bool operator==(const matrixGraph& arg) const;
	
	friend std::ostream& operator<< (std::ostream& stream, const matrixGraph& m);
private:
	std::vector<std::vector<int>> _matrix;


	bool isEmpty() const;
};

