#include "stdafx.h"
#include "DynamicController.h"
#include "TSPFileReader.h"


DynamicController::DynamicController(Application * const app)
	: Controller(app, new DynamicAlgorithm)
{}

void DynamicController::applyOnFile()
{
	auto fileName = getFilenameFromUser();
	auto graph = getGraph(fileName);
	m_algh->apply(&graph);
}

void DynamicController::applyOnFileVector()
{
	auto fileName = getFilenameFromUser();
	auto graph = getGraph(fileName);
	m_algh->apply(&graph);
}

void DynamicController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne na pojedynczym pliku", 
							std::bind(&DynamicController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne na plikach zapisanych w pliku",
							std::bind(&DynamicController::applyOnFileVector, this)));

}
