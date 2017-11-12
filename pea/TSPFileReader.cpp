#include "stdafx.h"
#include "TSPFileReader.h"


void TSPFileReader::tryParse()
{
	std::ifstream file(fileName, std::ifstream::in);

	if (file.is_open() && file.good())
	{
		std::vector<std::string> headerText, dataText;
		std::string line;
		TSPHeaderParser headerParser;

		while (getline(file, line))
		{
			if (isHeaderLine(line))
				headerText.push_back(line);
			else if (isDataLine(line))
				dataText.push_back(line);
			else if (isSectionLine(line))
				continue;
		}

		auto header = headerParser.parse(headerText);
		TSPDataParser dataParser(header);
		dataParser.parse(dataText);
		m_graph = dataParser.getGraph();
	}
	else
		throw std::invalid_argument("File couldn't be opened.");

	file.close();
}

matrixGraph TSPFileReader::getData()
{
	return m_graph;
}

bool TSPFileReader::isHeaderLine(const std::string & t_line) const
{
	return t_line.find(":") != std::string::npos;
}

bool TSPFileReader::isSectionLine(const std::string & t_line) const
{
	return t_line.find("SECTION") != std::string::npos;
}

bool TSPFileReader::isDataLine(const std::string & t_line) const
{
	return isDigit(t_line);
}

bool TSPFileReader::isDigit(const std::string & t_line) const
{
	if (t_line[0] > 47 && t_line[0] < 58)
		return true;
	else
		return false;
}
