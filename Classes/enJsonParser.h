#ifndef __ENJSON_PARSER_SCENE_H_
#define __ENJSON_PARSER_SCENE_H_

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"
USING_NS_CC;
//#include "MyUtility.h"

class enJsonParser :public cocos2d::Ref
{
private:
	ValueVector listData;
	std::string content;
public:

	static enJsonParser * createWithArray(ValueVector pListData);
	bool initWithArray(ValueVector pListData);

	//void encode(Information information,string order);
	string encode_WaitingRoomData();
	string encode_EnterGameData();
	string encode_MilitaryData();
	string encode_ConstructionData();
};

#endif