#ifndef __ENJSON_PARSER_SCENE_H_
#define __ENJSON_PARSER_SCENE_H_
//±àÂë
#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

#include <string>

USING_NS_CC;
using std::string;

class senJsonParser :public cocos2d::Ref
{
private:
	ValueVector listData;
	std::string content;
public:

	static senJsonParser * createWithArray(ValueVector pListData);

	bool initWithArray(ValueVector pListData);

	string encode_WaitingData();
	string encode_RoomData();
	string encode_EnterData();
	string encode_MilitaryData();
	string encode_ConstructionData();
};

#endif