#include "stdafx.h"
#include "TSPFileReader.h"


void TSPFileReader::tryParse()
{
	std::ifstream file(fileName, std::ifstream::in);

	if (file.is_open())
	{
		std::vector<std::string> headerText, dataText;
		std::string line;

		while (getline(file,line))
		{
			if (isHeaderLine(line))
				headerText.push_back(line);
			else if (isDataLine(line))
				dataText.push_back(line);
			else if (isSectionLine(line))
			{

			}
		}
	}

	file.close();
}

matrixGraph TSPFileReader::getData()
{
	return m_graph;
}

bool TSPFileReader::isHeaderLine(const std::string & t_line) const
{
	return !isSectionLine(t_line) && !isDigit(t_line);
}

bool TSPFileReader::isSectionLine(const std::string & t_line) const
{
	return t_line.find("SECTION") != t_line.end();
}

bool TSPFileReader::isDataLine(const std::string & t_line) const
{
	return isDigit(t_line);
}

bool TSPFileReader::isDigit(const std::string & t_line) const
{
	auto it = t_line.begin();
	while (it != t_line.end() && (std::isdigit(*it) || *it == '.'))
		++it;
	return !t_line.empty() && it == t_line.end();
}
