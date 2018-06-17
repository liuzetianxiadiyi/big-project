#ifndef __SJSON_PARSER_SCENE_H_
#define __SJSON_PARSER_SCENE_H_

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"
#include <string>
#include "GameData.h"
USING_NS_CC;
using std::string;
class sJsonParser :public cocos2d::Ref
{
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private:
	string content;
	cocos2d::ValueMap row;;

public:
	static sJsonParser * createWithC_str(const char * data);

	bool initWithC_str(const char * data);

	void decode_WaitingData();
	bool decode_RoomData();
	void decode_MilitaryData();
	void decode_ConstructionData();
};

#endif