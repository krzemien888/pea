#pragma once

#include "stdafx.h"
#include "TSPEnums.h"
#include "TSPHeader.h"
#include "TSPDataParser.h"

class TSPDataParserFactory
{
	TSPDataParserFactory() = default;
	~TSPDataParserFactory() = default;
public:

	static std::shared_ptr<TSPDataParser> getDataParser(const TSPHeader &header , std::string &section);

};

