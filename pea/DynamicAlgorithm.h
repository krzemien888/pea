#pragma once
#include "IAlgorithm.h"
#include "stdafx.h"


class DynamicAlgorithm final :
	public IAlgorithm
{
public:
	virtual ~DynamicAlgorithm() = default;
	virtual Result apply(matrixGraph* graph) override;

};

