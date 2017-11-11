#pragma once
#include "stdafx.h"
#include "IAlgorithm.h"
#include "Application.h"
#include "matrixGraph.h"

class Application;
class IAlghoritm;

class Controller 
{
public:
	Controller( Application* t_app,  IAlgorithm* t_algh);
	Controller() = delete;
	virtual ~Controller();
	virtual void registerOptions() = 0;
	virtual void applyOnFile();
	virtual void applyOnFileVector();


protected:

	matrixGraph getGraph(std::string fileName);
	std::list<matrixGraph> getGraphList(std::string fileName);
	std::string getFilenameFromUser();
	void saveResult(Result &result);

	Application*  m_app = nullptr;
	IAlgorithm * m_algh = nullptr;
};