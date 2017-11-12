#pragma once
#include "stdafx.h"

struct Result final
{
public:
	Result() = default;
	~Result() = default;

	std::string fileName = "";
	long int result = 0;
	long long int time = 0;
	friend std::ostream& operator<< (std::ostream& stream, const Result& r);
	std::vector<int> path;
};

