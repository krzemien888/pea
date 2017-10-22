#include "stdafx.h"
#include "FileReader.h"

void FileReader::setFileName(std::string name)
{
	fileName = name;
}

void FileReader::removeSpace(std::string s)
{
	while (s.find(' ') != std::string::npos)
	{
		size_t space = s.find(' ');
		s.erase(space, 1);
	}
}
