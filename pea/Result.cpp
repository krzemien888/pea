#include "stdafx.h"
#include "Result.h"

std::ostream & operator<<(std::ostream & stream, const Result & r)
{
	stream << "File name: " << r.fileName << " | result: " << r.result << " | time: " << r.time;
	stream << " | path: ";

	for (auto& v : r.path)
		stream << v << " -> ";
	stream << r.path[0] << std::endl;
	return stream;
}
