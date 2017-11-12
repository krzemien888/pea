#pragma once
#include "FileReader.h"

#include "stdafx.h"
#include "TSPHeaderParser.h"
#include "TSPDataParser.h"

class TSPFileReader :
	public FileReader
{
public:
	TSPFileReader() = default;
	virtual ~TSPFileReader() = default;

	virtual void tryParse();
	virtual matrixGraph getData();



	bool isHeaderLine(const std::string &t_line) const;
	bool isSectionLine(const std::string &t_line) const;
	bool isDataLine(const std::string &t_line) const;

private:
	bool isDigit(const std::string &t_line) const;

	
	matrixGraph m_graph;
};

