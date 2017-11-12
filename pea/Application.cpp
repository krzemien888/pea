#include "stdafx.h"
#include "Application.h"
#include "DynamicController.h"
#include "BruteforceController.h"

Application::Application()
{
	srand((unsigned int)time(NULL));

	addAction(Action(0, "Exit", [this](){
		Stop();
	}));

	controllers.push_back(std::make_shared<DynamicController>(this));
	controllers.push_back(std::make_shared<BruteforceController>(this));
	registerMenuOptions();
}

void Application::Run()
{
	running = true;
	std::string userInput;
	while (running)
	{
		system("cls");

		printActions();
		std::cout << "Podaj opcje: ";
		std::cin >> userInput;

		try {
			auto userAction = parseInput(userInput);
			userAction.Run();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
			system("pause");
		}

	}
}

void Application::Stop()
{
	running = false;
}

void Application::addAction(Action action)
{
	if (actions.find(action.getIndex()) != actions.end())
		throw std::invalid_argument("Action already registered");
	else
		actions[action.getIndex()] = action;
}

int Application::getFreeActionIndex()
{
	int out = 1;
	while (actions.find(out) != actions.end())
		out++;

	return out;
}

void Application::printActions()
{
	for (auto action : actions)
		std::cout << action.first << ": " << action.second.getName() << std::endl;
}

void Application::registerMenuOptions()
{
	for (auto controller : controllers)
		controller->registerOptions();
}

Action Application::parseInput(std::string input)
{
	int userChoice = std::stoi(input);

	auto userAction = actions.find(userChoice);

	if (userAction == actions.end())
	{
		throw std::invalid_argument("Nieprawidlowy argument");
	}
	else
		return userAction->second;

}


