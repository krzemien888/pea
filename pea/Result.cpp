#include "stdafx.h"
#include "Result.h"

std::ostream & operator<<(std::ostream & stream, const Result & r)
{
	stream << "File name: " << r.fileName << " | result: " << r.result << " | time: " << r.time << std::endl;
	return stream;
}
