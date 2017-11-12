#pragma once

#include "stdafx.h"


/**
 * In fact, this class should be named "MenuAction", but becouse of weird issue with VS I cannot create a file named like that.
**/

class Action
{
public:
	Action(int index, std::string name, std::function<void(void)> task);
	~Action() = default;
	Action();


	int getIndex() const;
	std::string getName() const;
	void Run();

	bool operator<(Action &other) const
	{
		return actionIndex < other.getIndex();
	}

private:
	int actionIndex;
	std::string actionName;
	std::function<void(void)> actionTask;
};

