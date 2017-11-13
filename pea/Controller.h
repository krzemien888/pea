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
	virtual void applyOnRandomGraph();
	virtual void applyFromSettings();
	virtual std::string getAlgorithmName() = 0;

protected:
	struct Setting
	{
		int cities;
		int times;
		std::string filename;
		bool symmetric;
	};

	matrixGraph getGraph(std::string fileName);
	std::list<matrixGraph> getGraphList(std::string fileName);
	std::string getFilenameFromUser();
	void saveResult(Result &result, bool app = false);

	Result generateAndRun(int cities, int times, bool symmetric);
	std::vector<Controller::Setting> readSettings(std::string & filename);
	std::vector<matrixGraph> getGraphFromSettings(std::vector<Controller::Setting> &settings);
	
	Application*  m_app = nullptr;
	IAlgorithm * m_algh = nullptr;

	

};