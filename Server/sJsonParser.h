#ifndef __SJSON_PARSER_SCENE_H_
#define __SJSON_PARSER_SCENE_H_

#include "json\json.h"
#include <string>
#include "GameData.h"
#include "Value.h"
using std::string;
class sJsonParser
{

private:
	string content;
	ValueMap row;;
	ValueMap information;

public:
	sJsonParser(const char* str)
	{
		content = str;
	}

	ValueMap getRow()
	{
		return row;
	}

	ValueMap getInformation()
	{
		return information;
	}

	void decode_WaitingData();
	bool decode_RoomData();
	//void decode_MilitaryData();
	//void decode_ConstructionData();
};

#endif