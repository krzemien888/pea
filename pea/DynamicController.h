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
	DynamicController(Application * const app);
	virtual ~DynamicController() = default;
	
	void applyOnFile();
	void applyOnFileVector();

private:
	void applyAndPrint(std::string inputFile);
	void applyAndSave(std::vector<std::string> inputFileVector, std::string outputFile);
	virtual void registerOptions() override;
};

