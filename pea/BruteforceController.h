#pragma once
#include "Controller.h"

class BruteforceController :
	public Controller
{
public:
	BruteforceController() = delete;
	BruteforceController(Application* app);
	virtual ~BruteforceController() = default;

	virtual void registerOptions() override;
};

