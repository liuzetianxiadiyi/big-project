#ifndef __JSON_PARSER_SCENE_H_
#define __JSON_PARSER_SCENE_H_

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"
USING_NS_CC;
#include <string>
using std::string;
class JsonParser:public cocos2d::Ref
{
	//CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private:
	string content;
	ValueMap row;
	string information;
	rapidjson::Document document;
public:
	static JsonParser * createWithC_str(const char * data);

	bool initWithC_str(const char * data);

	ValueMap decode_RoomNums();
	bool RoomNumsJuggle();
	ValueMap decode_WaitingData();
	bool WaitingDataJuggle();
	ValueMap decode_RoomData();
	bool RoomDataJuggle();
	int decode_EnterData();
	bool EnterDataJuggle();
	ValueMap decode_GameData();
	bool GameDataJuggle();

	string& getInformation()
	{
		return information;
	}
};

#endif