#include "stdafx.h"
#include "GeneticController.h"
#include "GeneticAlgorithm.h"

GeneticController::GeneticController(Application * app) : Controller(app, new GeneticAlgorithm)
{
}

std::string GeneticController::getAlgorithmName()
{
	std::string output("TabuSearch-");
	output.append(m_algh->toString());
	return output;
}

void GeneticController::registerOptions()
{
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami na pojedynczym pliku",
		std::bind(&GeneticController::applyOnFile, this)));
	m_app->addAction(Action(m_app->getFreeActionIndex(),
		"Przeszukiwanie z zakazami z zapisanych ustawien",
		std::bind(&GeneticController::applyFromSettings, this)));
}

void GeneticController::applyFromSettings()
{
	std::string filename = getFilenameFromUser();
	auto settings = readSettings(filename);
	auto graphVector = getGraphFromSettings(settings);
	system("cls");

	std::vector<Result> results;
	Result tmpResult;

	for (int i = 0; i < settings.size(); i++)
	{
		std::vector<long long int> times;
		if (graphVector[i].isGenerated())
			std::cout << "\nCalculating random graph of " << settings[i].cities << " cities\n";
		else
			std::cout << "Calculating " << settings[i].filename << '\n';

		for (int x = 0; x < settings[i].times; x++)
		{
			std::cout << "Starting " << x + 1 << " out of " << settings[i].times << '\r';
			auto tmpResult = m_algh->apply(&(graphVector[i]));

			times.push_back(tmpResult.time);
			results.push_back(tmpResult);
		}
		std::sort(results.begin(), results.end(), [](Result a, Result b) {
			return a.result > b.result;
		});
		Result worstResult = results[0];
		Result bestResult = results[results.size() - 1];
		Result avgResult;

		std::for_each(times.begin(), times.end(), [&](long long int n) {
			avgResult.time += n;
		});
		avgResult.time /= times.size();

		std::for_each(results.begin(), results.end(), [&](Result r) {
			avgResult.result += r.result;
		});
		avgResult.result /= results.size();

		std::ofstream stream;
		stream.open(filename + "-solutions-" + getAlgorithmName() + ".csv", std::ofstream::out | std::ofstream::app);

		if (stream.good())
		{
			if (graphVector[i].isGenerated())
			{
				stream << ((settings[i].symmetric) ? "tsp" : "atsp");
				stream << settings[i].cities << ";";
			}
			else
				stream << settings[i].filename << ";";

			stream << worstResult.result << ";" << worstResult.time << ";";
			for (auto &v : worstResult.path)
				stream << v << '-';
			stream << worstResult.path[0] << ";";


			stream << bestResult.result << ";" << bestResult.time << ";";
			for (auto &v : bestResult.path)
				stream << v << '-';
			stream << bestResult.path[0] << ";";


			stream << avgResult.result << ";" << avgResult.time << ";";
			stream << std::endl;
		}
		else
			throw std::logic_error("Couldn't save solution for " + filename + "-solutions-" + getAlgorithmName() + ".csv");

		stream.close();
		results.clear();
	}

}
