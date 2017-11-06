#pragma once
#include "IAlgorithm.h"
#include "Application.h"
#include "matrixGraph.h"

class Controller 
{
public:
	Controller() = delete;
	Controller(Application * const t_app, IAlgorithm * const t_algh);
	virtual ~Controller();
	virtual void registerOptions() = 0;

protected:

	matrixGraph getGraph(std::string fileName);
	std::list<matrixGraph> getGraphList(std::string fileName);
	std::string getFilenameFromUser();
	void saveResult(Result &result);


	Application* const m_app = nullptr;
	IAlgorithm * const m_algh = nullptr;
};