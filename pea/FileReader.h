#pragma once

#include "matrixGraph.h"

class FileReader
{
public:
	FileReader() = default;
	virtual ~FileReader() = default;

	virtual void setFileName(std::string name);
	virtual void tryParse() = 0;
	virtual matrixGraph getData() = 0;

protected:
	void removeSpace(std::string s);

private:
	std::string fileName;
};

