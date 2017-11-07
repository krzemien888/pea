#pragma once

#include "stdafx.h"

#include "Action.h"
#include "matrixGraph.h"
#include "Controller.h"

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
	std::vector<std::shared_ptr<Controller>> controllers;
	matrixGraph graph;
};