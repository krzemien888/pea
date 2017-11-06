#pragma once

#include "stdafx.h"

#include "Action.h"
#include "matrixGraph.h"

class Application final
{
public:
	Application();
	~Application() = default;
	void Run();
	void Stop();
	void addAction(Action action);
	int getFreeActionIndex();
private:
	void printActions();
	Action parseInput(std::string input);
	bool running = false;
	std::map<int, Action> actions;

	matrixGraph graph;
};