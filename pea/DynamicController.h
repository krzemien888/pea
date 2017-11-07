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
	
	void applyOnFile();
	void applyOnFileVector();

private:
	virtual void registerOptions() override;
};

