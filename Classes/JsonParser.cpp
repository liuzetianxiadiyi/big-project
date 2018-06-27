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

ValueMap JsonParser::decode_WaitingData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//解码，0为解析标识（默认值）

	CC_ASSERT(document.IsObject());

	row = ValueMap();

	if (document.HasMember(SWAITINGSCENEDATA))		//for server
	{
		const rapidjson::Value &temp = document[SWAITINGSCENEDATA];

		const rapidjson::Value &val_add = temp[ADDROOM];
		row[ADDROOM] = Value(val_add.GetInt());

		const rapidjson::Value &val_rLabel = temp[ROOMLABEL];
		ValueVector rTemp;
		for (auto& r : val_rLabel.GetArray())
		{
			rTemp.push_back(Value(r.GetInt()));
		}
		row[ROOMLABEL] = Value(rTemp);

		const rapidjson::Value& val_del = temp[DELETED];
		row[DELETED] = val_del.GetBool();

		if (val_del.GetBool())
		{
			ValueVector dTemp;
			const rapidjson::Value& val_rDel = temp[DELETEDROOM];
			for (auto& d : val_rDel.GetArray())
			{
				dTemp.push_back(Value(d.GetInt()));
			}
			row[DELETEDROOM] = Value(dTemp);
		}
	}

	return row;
}

ValueMap JsonParser::decode_RoomData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//解码，0为解析标识（默认值）

	CC_ASSERT(document.IsObject());

	if (document.HasMember(SROOMSCENEDATA))		//for server
	{
		const rapidjson::Value &temp = document[SROOMSCENEDATA];

		/*const rapidjson::Value &val_own = temp[OWNER];
		row[OWNER] = Value(val_own.GetString());*/

		ValueVector vName;
		const rapidjson::Value &val_mem = temp[MEMBER];
		for (auto& v : val_mem.GetArray())
		{
			vName.push_back(Value(v.GetString()));
		}
		row[MEMBER] = Value(vName);
	}

	return row;
}

int JsonParser::decode_EnterData()
{
	using namespace RoomMessage;
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//解码，0为解析标识（默认值）

	CC_ASSERT(document.IsObject());
	//取一条记录对象

	if (document.HasMember(SENTERROOMDATA))		//for server
	{
		const rapidjson::Value &temp = document[SENTERROOMDATA];

		const rapidjson::Value &val_own = temp[ISSTART];
		if (val_own.GetBool())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (document.HasMember(ADDNAME))
	{
		const rapidjson::Value& name = document[ADDNAME];
		information = name.GetString();
		return -1;
	}

	//list.push_back(Value(row));
}

ValueMap JsonParser::decode_GameData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());

	CC_ASSERT(document.IsArray());


	row = ValueMap();
	ValueMap Military_map;

	if (document.HasMember(MILITARYDATA))		//获得dogdata等
	{
		const rapidjson::Value &temp = document[MILITARYDATA];

		const rapidjson::Value &val_dog = temp[DOGDATA];	//val_dog为包含多个map的数组，一个元素代表一个兵
		const rapidjson::Value &val_sold = temp[SOLDIERDATA];
		const rapidjson::Value &val_eng = temp[ENGINEERDATA];

		ValueVector dogdata;
		ValueVector soldierdata;
		ValueVector engineerdata;

		for (auto& v : val_dog.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[DESTINATIONX] = v.GetObjectW()[DESTINATIONX].GetFloat();
			temp_map[DESTINATIONY] = v.GetObjectW()[DESTINATIONY].GetFloat();
			temp_map[STATUS] = v.GetObjectW()[STATUS].GetString();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			dogdata.push_back(Value(temp_map));
		}
		for (auto& v : val_sold.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[DESTINATIONX] = v.GetObjectW()[DESTINATIONX].GetFloat();
			temp_map[DESTINATIONY] = v.GetObjectW()[DESTINATIONY].GetFloat();
			temp_map[STATUS] = v.GetObjectW()[STATUS].GetString();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			soldierdata.push_back(Value(temp_map));
		}
		for (auto& v : val_eng.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[DESTINATIONX] = v.GetObjectW()[DESTINATIONX].GetFloat();
			temp_map[DESTINATIONY] = v.GetObjectW()[DESTINATIONY].GetFloat();
			temp_map[STATUS] = v.GetObjectW()[STATUS].GetString();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			engineerdata.push_back(Value(temp_map));
		}

		pair<string, Value> pair0 = make_pair(DOGDATA, Value(dogdata));
		pair<string, Value> pair1 = make_pair(SOLDIERDATA, Value(soldierdata));
		pair<string, Value> pair2 = make_pair(ENGINEERDATA, Value(engineerdata));
		Military_map = GameData::toValueMap({ pair0,pair1,pair2 });
	}
	
	ValueMap Construction_map;
	if (document.HasMember(CONSTRUCTIONDATA))		//获得dogdata等
	{
		const rapidjson::Value &temp = document[CONSTRUCTIONDATA];

		const rapidjson::Value &val_bar = temp[BARRACKSDATA];
		const rapidjson::Value &val_war = temp[WARFACTORYDATA];
		const rapidjson::Value &val_min = temp[MINEDATA];
		const rapidjson::Value &val_bas = temp[BASEDATA];

		ValueVector bardata;
		ValueVector wardata;
		ValueVector mindata;
		ValueVector basdata;

		for (auto& v : val_bar.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			bardata.push_back(Value(temp_map));
		}
		for (auto& v : val_war.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			wardata.push_back(Value(temp_map));
		}
		for (auto& v : val_min.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			mindata.push_back(Value(temp_map));
		}
		for (auto& v : val_bas.GetArray())
		{
			ValueMap temp_map;
			temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
			temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
			temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
			temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
			temp_map[STAG] = v.GetObjectW()[STAG].GetInt();
			basdata.push_back(Value(temp_map));
		}

		pair<string, Value> pair0 = make_pair(BARRACKSDATA, Value(bardata));
		pair<string, Value> pair1 = make_pair(WARFACTORYDATA, Value(wardata));
		pair<string, Value> pair2 = make_pair(MINEDATA, Value(mindata));
		pair<string, Value> pair3 = make_pair(BASEDATA, Value(basdata));
		Construction_map = GameData::toValueMap({ pair0,pair1,pair2,pair3 });
	}

	pair<string, Value> mPair = make_pair(MILITARYDATA, Value(Military_map));
	pair<string, Value> cPair = make_pair(CONSTRUCTIONDATA, Value(Construction_map));
	return GameData::toValueMap({ mPair,cPair });
}