#pragma once
#include "IAlgorithm.h"
#include "Application.h"

class Controller 
{
public:
	Controller() = delete;
	Controller(Application * const t_app, IAlgorithm * const t_algh) : m_app(t_app), m_algh(t_algh) {};
	virtual ~Controller() {
		if (m_algh != nullptr) delete m_algh;
	};

protected:
	Application* const m_app = nullptr;
	IAlgorithm * const m_algh = nullptr;
};