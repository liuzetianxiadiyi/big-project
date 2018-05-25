#include "senJsonParser.h"
#include "GameData.h"

senJsonParser * senJsonParser::createWithArray(ValueVector pListData)
{
	senJsonParser * pRef = new senJsonParser();

	if (pRef->initWithArray(pListData))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

bool senJsonParser::initWithArray(ValueVector pListData)
{
	listData = pListData;
	return true;
}

void senJsonParser::encode(string& sendBuf, string order)		//这里换成message防止直接使用全局变量information造成未知的bug
{
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法

	rapidjson::Value array(rapidjson::kArrayType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();				//这里的v就是map，Value是一种包装类，可以把很多数据类型包装成类

		rapidjson::Value object(rapidjson::kObjectType);
		if (order == ROOMMATE)
		{
			ValueMap row = temp[ROOMMATE].asValueMap();
			rapidjson::Value v_map(rapidjson::kObjectType);

			rapidjson::Value v_add;
			v_add.SetBool(row[ADDROOM].asBool());
			v_map.AddMember(ADDROOM, v_add, allocator);

			rapidjson::Value v_rTag;
			v_rTag.SetInt(row[ROOMLABEL].asInt());
			v_map.AddMember(ROOMLABEL, v_rTag, allocator);

			rapidjson::Value v_name;
			v_name.SetString(row[PLAYERNAME].asString().c_str(), allocator);
			v_map.AddMember(PLAYERNAME, v_name, allocator);

			object.AddMember(SWAITINGSCENEDATA, v_map, allocator);
		}

		array.PushBack(object, allocator);
	}

	//document.AddMember("change", true, allocator);
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	sendBuf = buffer.GetString();
	//log("out: %s", out);
}