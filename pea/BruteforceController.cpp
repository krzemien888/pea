#include "stdafx.h"
#include "BruteforceController.h"
#include "BruteforceAlgorithm.h"


BruteforceController::BruteforceController(Application * app)
	: Controller(app, new BruteforceAlgorithm)
{}

void BruteforceController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukanie zupe³ne na pojedynczym pliku",
		std::bind(&BruteforceController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukanie zupe³ne na plikach zapisanych w pliku",
		std::bind(&BruteforceController::applyOnFileVector, this)));
}
