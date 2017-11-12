#include "stdafx.h"
#include "Controller.h"
#include "TSPFileReader.h"

Controller::Controller( Application * t_app,  IAlgorithm * t_algh)
	: m_app(t_app), m_algh(t_algh)
{
}

Controller::~Controller()
{
	if (m_algh != nullptr) 
		delete m_algh;
}

void Controller::applyOnFile()
{
	auto fileName = getFilenameFromUser();
	auto graph = getGraph(fileName);
	auto result = m_algh->apply(&graph);
	result.fileName = graph.getName();

	system("cls");
	std::cout << result;
	system("pause");
}

void Controller::applyOnFileVector()
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

matrixGraph Controller::getGraph(std::string fileName)
{
	TSPFileReader tspParser;

	tspParser.setFileName(fileName);
	try {
		tspParser.tryParse();
	}
	catch (std::exception &e)
	{
		std::cout << "Wystapil blad podczas parsowania pliku\n" << e.what() << std::endl;
		throw std::invalid_argument("Controller: Parse error");
	}

	auto graph = tspParser.getData();
	graph.setName(fileName);
	return graph;
}

std::list<matrixGraph> Controller::getGraphList(std::string fileName)
{
	std::list<matrixGraph> output;
	std::stringstream ss(fileName);
	std::string line;
	while (getline(ss, line))
		output.push_back(getGraph(line));

	return output;
}

std::string Controller::getFilenameFromUser()
{
	std::string userInput;
	TSPFileReader tspParser;
	bool keepLoop = true;
	while (keepLoop)
	{
		try {
			std::cout << "Podaj nazwe pliku: ";
			std::cin >> userInput;
			tspParser.setFileName(userInput);
			keepLoop = false;
		}
		catch (std::invalid_argument)
		{
			keepLoop = true;
			std::cout << "Nie udalo sie otworzyc pliku " << userInput << ".\n";
		}
	}
	return userInput;
}

void Controller::saveResult(Result & result)
{
	std::ofstream stream(result.fileName + "Answer.txt", std::ofstream::out);

	if (stream.good())
		stream << result.fileName << ";" << result.result << ";" << result.time << std::endl;
	else
		throw std::logic_error("Couldn't save solution for " + result.fileName);
}

