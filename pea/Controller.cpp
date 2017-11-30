#include "stdafx.h"
#include "Controller.h"
#include "TSPFileReader.h"

struct Controller::Setting;

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

void Controller::applyOnRandomGraph()
{
	int cities;
	int times;
	char symmetric;
	std::cout << "Liczba miast:";
	std::cin >> cities;
	std::cout << "\nLiczba przebiegow:";
	std::cin >> times;
	std::cout << "\n";
	std::cout << "TSP[t/n]:";
	std::cin >> symmetric;

	system("cls");
	auto result = generateAndRun(cities, times, symmetric=='t');

	result.fileName = "randomGenerated";
	std::cout << result;
	system("pause");

}

void Controller::applyFromSettings()
{
	std::string filename = getFilenameFromUser();
	auto settings = readSettings(filename);
	auto graphVector = getGraphFromSettings(settings);
	system("cls");

	for (int i = 0; i < settings.size(); i++)
	{
		Result finalResult;
		std::vector<long long int> times;
		if (graphVector[i].isGenerated())
			std::cout << "\nCalculating random graph of " << settings[i].cities << " cities\n";
		else
			std::cout << "Calculating " << settings[i].filename << '\n';

		for (int x = 0; x < settings[i].times; x++)
		{
			std::cout << "Starting " << x + 1 << " out of " << settings[i].times << '\r';
			auto tmpResult = m_algh->apply(&(graphVector[i]));
			if (finalResult.path.empty())
				finalResult = tmpResult;
			times.push_back(tmpResult.time);
		}

		std::for_each(times.begin(), times.end(), [&](long long int n) {
			finalResult.time += n;
		});
		
		finalResult.time /= times.size();
		

		std::ofstream stream;	
		stream.open(filename + "-solutions-"+getAlgorithmName()+".csv", std::ofstream::out | std::ofstream::app);

		if (stream.good())
		{
			if (graphVector[i].isGenerated())
			{
				stream << ((settings[i].symmetric) ? "tsp" : "atsp");
				stream << settings[i].cities << ";";
			}
			else
				stream << settings[i].filename << ";";
			stream << finalResult.result << ";" << finalResult.time << ";";
			for (auto &v : finalResult.path)
				stream << v << '-';
			stream << finalResult.path[0];
			stream << std::endl;
		}
		else
			throw std::logic_error("Couldn't save solution for " + finalResult.fileName);

		stream.close();
	}
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

void Controller::saveResult(Result & result, bool app)
{
	
	std::ofstream stream;

	if (app)
		stream.open(result.fileName + "Answer.txt", std::ofstream::out | std::ofstream::app);
	else
		stream.open(result.fileName + "Answer.txt", std::ofstream::out);

	if (stream.good())
		stream << result.fileName << ";" << result.result << ";" << result.time << std::endl;
	else
	{
		stream.close();
		throw std::logic_error("Couldn't save solution for " + result.fileName);
	}

	stream.close();
}

Result Controller::generateAndRun(int cities, int times, bool symmetric)
{
	matrixGraph graph = matrixGraph::generate(cities, symmetric);
	
	auto result = m_algh->apply(&graph);
	result.fileName = graph.getName();

	std::cout << graph;
	return result;
}

std::vector<Controller::Setting> Controller::readSettings(std::string & filename)
{
	std::ifstream file(filename, std::ifstream::in);
	std::vector<Setting> settingVector;
	std::string line;
	if (file.is_open() && file.good())
	{
		while (getline(file, line))
		{
			std::stringstream ss(line);
			Controller::Setting settings;
			if (line[0] > 47 && line[0] < 58)
			{
				ss >> settings.cities;
				ss >> settings.symmetric;
			}
			else
			{
				ss >> settings.filename;
			}

			ss >> settings.times;

			settingVector.push_back(settings);
		}
	}
	else
		throw std::invalid_argument("Controller::readSettings: setting parse error.");

	file.close();
	return settingVector;
}

std::vector<matrixGraph> Controller::getGraphFromSettings(std::vector<Setting>& settings)
{
	std::vector<matrixGraph> output;
	for (auto &setting : settings)
	{
		matrixGraph graph;
		if (!setting.filename.empty())
		{
			graph = getGraph(setting.filename);
		}
		else
		{
			graph = matrixGraph::generate(setting.cities, setting.symmetric);
		}
		output.push_back(graph);
	}
	return output;
}

