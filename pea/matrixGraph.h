#pragma once

#include "stdafx.h"

class matrixGraph
{
public:

	static matrixGraph generate(const int vertexCount, const bool symmetric, const int minValue = 1, const int maxValue = 600);

	matrixGraph() = default;
	~matrixGraph() = default;

	void setMatrix(std::vector<std::vector<int>> &matrix);
	void setConnection(const int from, const int to, const int value);
	void addVertex();
	void addVertex(unsigned int newSize);

	int getConnectionValue(const size_t from, const size_t to) const;
	std::vector<int> getNeighbours(const int vectex) const; 
	float getDensity() const;
	size_t getSize() const ;
	std::string getName();
	void setName(std::string t_name);

	bool operator==(const matrixGraph& arg) const;
	
	friend std::ostream& operator<< (std::ostream& stream, const matrixGraph& m);
	
private:
	std::vector<std::vector<int>> _matrix;
	std::string m_name;

	bool isEmpty() const;
};

