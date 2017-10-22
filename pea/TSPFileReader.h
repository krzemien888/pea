#pragma once
#include "FileReader.h"

class TSPFileReader :
	public FileReader
{
public:
	TSPFileReader() = default;
	virtual ~TSPFileReader() = default;

	virtual void tryParse();
	virtual matrixGraph getData();
};

