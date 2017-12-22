#pragma once
#include "IAlgorithm.h"


class GeneticAlgorithm :
	public IAlgorithm
{
public:
	virtual ~GeneticAlgorithm() = default;

	virtual Result apply(matrixGraph* graph) override;
	virtual std::string toString() override;
};

