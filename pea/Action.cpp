#include "stdafx.h"
#include "Action.h"

Action::Action(int index, std::string name, std::function<void(void)> task)
	:	actionIndex(index),
		actionName(name),
		actionTask(task)
{
}

Action::Action()
{
	actionIndex = 15;
	actionName = std::string("Default action");
	actionTask = []() {std::cout << "Default action taken" << std::endl;system("pause");};
}

int Action::getIndex() const
{
	return actionIndex;
}

std::string Action::getName() const
{
	return actionName;
}

void Action::Run()
{
	actionTask();
}
