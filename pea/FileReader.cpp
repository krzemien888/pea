#include "stdafx.h"
#include "FileReader.h"

void FileReader::setFileName(std::string name)
{
	std::ifstream file(name, std::ifstream::in);

	if (file.is_open() && file.good())
		fileName = name;
	else
		throw std::invalid_argument("File couln't be opened");


}

void FileReader::removeSpace(std::string s)
{
	while (s.find(' ') != std::string::npos)
	{
		size_t space = s.find(' ');
		s.erase(space, 1);
	}
}
