#include "stdafx.h"
#include "BruteforceController.h"
#include "BruteforceAlgorithm.h"


BruteforceController::BruteforceController(Application * app)
	: Controller(app, new BruteforceAlgorithm)
{}

void BruteforceController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Bruteforce na pojedynczym pliku",
		std::bind(&BruteforceController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Bruteforce na plikach zapisanych w pliku",
		std::bind(&BruteforceController::applyOnFileVector, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Bruteforce na losowym grafie",
		std::bind(&BruteforceController::applyOnRandomGraph, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Bruteforce z zapisanych ustawien",
		std::bind(&BruteforceController::applyFromSettings, this)));
}
