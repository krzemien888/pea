#pragma once
#include "Controller.h"
class GeneticController :
	public Controller
{
public:
	GeneticController() = delete;
	GeneticController(Application * app);
	virtual ~GeneticController() = default;

	virtual std::string getAlgorithmName() override;
	virtual void registerOptions() override;
	virtual void applyFromSettings() override;
};

