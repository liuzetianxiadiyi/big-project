#ifndef __JSON_PARSER_SCENE_H_
#define __JSON_PARSER_SCENE_H_

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"
#include "Information.h"

class JsonParser:public cocos2d::Ref
{
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private:
	string content;
	cocos2d::ValueMap row;

public:
	static JsonParser * createWithC_str(const char * data);

	bool initWithC_str(const char * data);

	void decode_WaitingData();
	void decode_RoomData();
	bool decode_EnterData();
	void decode_MilitaryData();
	void decode_ConstructionData();
};

#endif