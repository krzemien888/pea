#include "stdafx.h"
#include "Application.h"


Application::Application()
{
	addAction(Action(0, "Exit", [this](){
		Stop();
	}));


	srand((unsigned int)time(NULL));
}

void Application::Run()
{
	running = true;
	std::string userInput;
	while (running)
	{
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
	actions[action.getIndex()] = action;
}

void Application::printActions()
{
	for (auto action : actions)
		std::cout << action.first << ": " << action.second.getName() << std::endl;
}

Action Application::parseInput(std::string input)
{
	int userChoice = std::stoi(input);

	auto userAction = actions.find(userChoice);

	if (userAction == actions.end())
	{
		throw std::invalid_argument("Nieprawid³owy argument");
	}
	else
		return userAction->second;

}


