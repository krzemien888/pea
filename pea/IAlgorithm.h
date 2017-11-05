#pragma once
#include "stdafx.h"
#include "matrixGraph.h"
#include "Result.h"

class IAlgorithm
{
public:
	virtual Result apply(matrixGraph* graph) = 0;
	virtual ~IAlgorithm() = default;
};