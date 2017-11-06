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
	friend std::ostream& operator<< (std::ostream& stream, const Result& r);
};

