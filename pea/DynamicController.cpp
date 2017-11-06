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
	auto result = m_algh->apply(&graph);
	result.fileName = graph.getName();

	system("cls");
	std::cout << result;
	system("pause");
}

void DynamicController::applyOnFileVector()
{
	auto fileName = getFilenameFromUser();
	auto graphs = getGraphList(fileName);

	std::list<Result> results;

	for (auto &graph : graphs)
	{
		auto result = m_algh->apply(&graph);
		result.fileName = graph.getName();
		results.push_back(result);
	}

	for (auto &result : results)
		saveResult(result);
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
