#include "sJsonParser.h"
//#include "platform/CCFileUtils.h"
using std::make_pair;

void sJsonParser::decode_WaitingData()
{
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(content, root))
	{
		Json::Value vTemp = root[WAITINGSCENEDATA];
		row[ADDROOM] = MyValue(vTemp[ADDROOM].asBool());

		row[ROOMLABEL] = MyValue(vTemp[ROOMLABEL].asInt());

		row[PLAYERNAME] = MyValue(vTemp[PLAYERNAME].asString());
	}

	information[WAITINGSCENEDATA] = MyValue(row);
}

bool sJsonParser::decode_RoomData()
{
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(content, root))
	{
		Json::Value vTemp = root[ROOMSCENEDATA];
		if (vTemp[ISSTART].asBool)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*void sJsonParser::decode_MilitaryData()
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

		if (record.HasMember(MILITARYDATA))		//获得dogdata等
		{
			const rapidjson::Value &temp = record[MILITARYDATA];

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
				engineerdata.push_back(Value(temp_map));
			}

			pair<string, Value> pair0 = make_pair(DOGDATA, Value(dogdata));
			pair<string, Value> pair1 = make_pair(SOLDIERDATA, Value(soldierdata));
			pair<string, Value> pair2 = make_pair(ENGINEERDATA, Value(engineerdata));
			row = GameData::toValueMap({ pair0,pair1,pair2 });
		}
		list.push_back(Value(row));
	}
}

void sJsonParser::decode_ConstructionData()
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

		if (record.HasMember(CONSTRUCTIONDATA))		//获得dogdata等
		{
			const rapidjson::Value &temp = record[CONSTRUCTIONDATA];

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
				bardata.push_back(Value(temp_map));
			}
			for (auto& v : val_war.GetArray())
			{
				ValueMap temp_map;
				temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
				temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
				temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
				temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
				wardata.push_back(Value(temp_map));
			}
			for (auto& v : val_min.GetArray())
			{
				ValueMap temp_map;
				temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
				temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
				temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
				temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
				mindata.push_back(Value(temp_map));
			}
			for (auto& v : val_bas.GetArray())
			{
				ValueMap temp_map;
				temp_map[HEALTHPOINT] = v.GetObjectW()[HEALTHPOINT].GetInt();
				temp_map[POSITIONX] = v.GetObjectW()[POSITIONX].GetFloat();
				temp_map[POSITIONY] = v.GetObjectW()[POSITIONY].GetFloat();
				temp_map[COUNTRY] = v.GetObjectW()[COUNTRY].GetInt();
				basdata.push_back(Value(temp_map));
			}

			pair<string, Value> pair0 = make_pair(BARRACKSDATA, Value(bardata));
			pair<string, Value> pair1 = make_pair(WARFACTORYDATA, Value(wardata));
			pair<string, Value> pair2 = make_pair(MINEDATA, Value(mindata));
			pair<string, Value> pair3 = make_pair(BASEDATA, Value(basdata));
			row = GameData::toValueMap({ pair0,pair1,pair2,pair3 });
		}
		list.push_back(Value(row));
	}
}*/