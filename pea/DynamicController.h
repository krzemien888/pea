#pragma once
#include "Controller.h"
#include "stdafx.h"
#include "Application.h"
#include "DynamicAlgorithm.h"

class DynamicController final:
	public Controller
{
public:
	DynamicController() = delete;
	DynamicController(Application * app);
	virtual ~DynamicController() = default;
	virtual std::string getAlgorithmName() override {
		return "DP";
	};
	virtual void registerOptions() override;

};

