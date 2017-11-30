#pragma once
#include "Controller.h"
class TabuSearchController :
	public Controller
{
public:
	TabuSearchController() = delete;
	TabuSearchController(Application * app);
	virtual ~TabuSearchController() = default;

	virtual std::string getAlgorithmName() override;
	virtual void registerOptions() override;
};

