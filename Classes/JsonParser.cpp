#include "JsonParser.h"
#include "platform/CCFileUtils.h"
#include "GameData.h"
USING_NS_CC;
/*JsonParser * JsonParser::createWithFile(const char * filename)
{
	JsonParser *pRet = new JsonParser();
	if (pRet->initWithFile(filename))
	{
		pRet->autorelease();		//自动释放
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

bool JsonParser::initWithFile(const char * filename)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string path = sharedFileUtils->fullPathForFilename(filename);
	Data data = sharedFileUtils->getDataFromFile(path);
	content = std::string((const char *)data.getBytes(), 0, data.getSize());

	return true;
}*/

JsonParser * JsonParser::createWithC_str(const char * data)
{
	JsonParser * pRef = new JsonParser();

	if (pRef->initWithC_str(data))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

bool JsonParser::initWithC_str(const char * data)
{
	content = data;
	return true;
}

void JsonParser::decode()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//解码，0为解析标识（默认值）

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//判断是否是有效对象，是否有record数据项

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();
		ValueMap temp_map = ValueMap();

		//取一条记录对象
		const rapidjson::Value &record = records[i];

		if (record.HasMember(WAITINGSCENEDATA))	
		{
			const rapidjson::Value &temp = record[WAITINGSCENEDATA];

			const rapidjson::Value &val_nums = temp[ADDROOM];
			temp_map[ADDROOM] = Value(val_nums.GetInt());

			const rapidjson::Value &val_rLabel = temp[ROOMLABEL];
			ValueVector Room_Label;
			for (int i = 0; i < val_rLabel.GetArray().Size();++i)
			{
				Room_Label.push_back(Value(val_rLabel[i].GetInt()));
			}
			temp_map[ROOMLABEL] = Value(Room_Label);

			const rapidjson::Value &isDeleted = temp[DELETED];
			temp_map[DELETED] = Value(isDeleted.GetBool());
			
			if (isDeleted.GetBool())
			{
				const rapidjson::Value &Deleted_Tag = temp[DELETEDROOM];
				ValueVector Deleted_Label;
				for (int i = 0; i < Deleted_Tag.GetArray().Size(); ++i)
				{
					Deleted_Label.push_back(Value(Deleted_Tag[i].GetInt()));
				}
				temp_map[ROOMLABEL] = Value(Deleted_Label);
			}
			
			row[WAITINGSCENEDATA] = Value(temp_map);
		}

		list.push_back(Value(row));
	}
}