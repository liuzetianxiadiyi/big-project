#ifndef __ENJSON_PARSER_SCENE_H_
#define __ENJSON_PARSER_SCENE_H_
//±àÂë
#include "Value.h"
#include "json\json.h"

#include <string>
#include "GameData.h"
using std::string;

class senJsonParser
{
private:
	ValueVector listData;
	std::string content;
public:

	senJsonParser(ValueVector pListData);

	string encode_RoonNums();
	string encode_WaitingData();
	string encode_RoomData();
	string encode_EnterData();
	string encode_aRoomData();
	//string encode_MilitaryData();
	//string encode_ConstructionData();
};

#endif