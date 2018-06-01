#include "JsonParser.h"
#include "platform/CCFileUtils.h"
#include "GameData.h"
USING_NS_CC;
/*JsonParser * JsonParser::createWithFile(const char * filename)
{
	JsonParser *pRet = new JsonParser();
	if (pRet->initWithFile(filename))
	{
		pRet->autorelease();		//�Զ��ͷ�
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

void JsonParser::decode_WaitingData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		if (record.HasMember(SWAITINGSCENEDATA))		//for server
		{
			const rapidjson::Value &temp = record[SWAITINGSCENEDATA];

			const rapidjson::Value &val_add = temp[ADDROOM];
			row[ADDROOM] = Value(val_add.GetBool());

			const rapidjson::Value &val_rLabel = temp[ROOMLABEL];
			row[ROOMLABEL] = Value(val_rLabel.GetInt());

			const rapidjson::Value &val_name = temp[PLAYERNAME];
			row[PLAYERNAME] = Value(val_name.GetString());
		}

		list.push_back(Value(row));
	}
}

void JsonParser::decode_RoomData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		if (record.HasMember(SROOMSCENEDATA))		//for server
		{
			const rapidjson::Value &temp = record[SROOMSCENEDATA];

			const rapidjson::Value &val_own = temp[OWNER];
			row[OWNER] = Value(val_own.GetString());

			ValueVector vName;
			const rapidjson::Value &val_mem = temp[MEMBER];
			for (auto& v : val_mem.GetArray())
			{
				vName.push_back(Value(v.GetInt()));
			}
			row[MEMBER] = Value(vName);
		}

		list.push_back(Value(row));
	}
}

bool JsonParser::decode_EnterData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		if (record.HasMember(SENTERROOMDATA))		//for server
		{
			const rapidjson::Value &temp = record[SENTERROOMDATA];

			const rapidjson::Value &val_own = temp[ISSTART];
			if (val_own.GetBool())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//list.push_back(Value(row));
	}
}

void JsonParser::decode_MilitaryData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();
		ValueMap temp_map = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		if (record.HasMember(MILITARYDATA))		//���dogdata��
		{
			const rapidjson::Value &temp = record[MILITARYDATA];

			const rapidjson::Value &val_dog = temp[DOGDATA];	//val_dogΪ�������map�����飬һ��Ԫ�ش���һ����
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

void JsonParser::decode_ConstructionData()
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());		//���룬0Ϊ������ʶ��Ĭ��ֵ��

	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	log("Parsing to document succeeded");
	CC_ASSERT(document.IsObject() && document.HasMember("Record"));		//�ж��Ƿ�����Ч�����Ƿ���record������

	const rapidjson::Value& records = document["Record"];

	CC_ASSERT(records.IsArray());

	for (unsigned int i = 0; i < records.Size(); ++i)
	{
		row = ValueMap();
		ValueMap temp_map = ValueMap();

		//ȡһ����¼����
		const rapidjson::Value &record = records[i];

		if (record.HasMember(CONSTRUCTIONDATA))		//���dogdata��
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
}