#include "stdafx.h"
#include "TabuSearchController.h"
#include "TabuSearchAlgorithm.h"


TabuSearchController::TabuSearchController(Application * app) : Controller(app, new TabuSearchAlgorithm)
{
}

std::string TabuSearchController::getAlgorithmName()
{
	return "TabuSearch";
}

void TabuSearchController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami na pojedynczym pliku",
		std::bind(&TabuSearchController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami na plikach zapisanych w pliku",
		std::bind(&TabuSearchController::applyOnFileVector, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami na losowym grafie",
		std::bind(&TabuSearchController::applyOnRandomGraph, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami z zapisanych ustawien",
		std::bind(&TabuSearchController::applyFromSettings, this)));
}

