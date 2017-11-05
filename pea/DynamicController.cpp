#include "stdafx.h"
#include "DynamicController.h"
#include "TSPFileReader.h"


DynamicController::DynamicController(Application * const app)
	: Controller(app, new DynamicAlgorithm)
{

}

void DynamicController::applyOnFile()
{
}

void DynamicController::applyOnFileVector()
{
}

void DynamicController::applyAndPrint(std::string inputFile)
{
}

void DynamicController::applyAndSave(std::vector<std::string> inputFileVector, std::string outputFile)
{
}

void DynamicController::registerOptions()
{

}
