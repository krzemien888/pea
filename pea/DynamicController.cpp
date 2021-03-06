#include "stdafx.h"
#include "DynamicController.h"
#include "TSPFileReader.h"


DynamicController::DynamicController(Application * app)
	: Controller(app, new DynamicAlgorithm)
{}

void DynamicController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne na pojedynczym pliku", 
							std::bind(&DynamicController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne na plikach zapisanych w pliku",
							std::bind(&DynamicController::applyOnFileVector, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne na losowym grafie",
							std::bind(&DynamicController::applyOnRandomGraph, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
							"Programowanie dynamiczne z zapisanych ustawien",
							std::bind(&DynamicController::applyFromSettings, this)));
}
