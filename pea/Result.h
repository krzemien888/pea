#pragma once
#include "stdafx.h"

struct Result final
{
public:
	Result() = default;
	~Result() = default;

	std::string fileName;
	long int result;
	long long int time;
};

