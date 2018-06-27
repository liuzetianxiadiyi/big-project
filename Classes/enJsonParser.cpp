#include "enJsonParser.h"
#include "GameData.h"

USING_NS_CC;

enJsonParser * enJsonParser::createWithArray(ValueVector pListData)
{
	enJsonParser * pRef = new enJsonParser();

	if (pRef->initWithArray(pListData))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

bool enJsonParser::initWithArray(ValueVector pListData)
{
	listData = pListData;
	return true;
}
//
//void enJsonParser::encode(Information message,string order)		//这里换成message防止直接使用全局变量information造成未知的bug
//{
//	rapidjson::Document document;
//	document.SetObject();		//初始化document
//	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法
//
//	rapidjson::Value array(rapidjson::kArrayType);
//
//	for (auto& v : listData)
//	{
//		ValueMap temp = v.asValueMap();				//这里的v就是map，Value是一种包装类，可以把很多数据类型包装成类
//
//		rapidjson::Value object(rapidjson::kObjectType);
//		if (order == ENTERROOMDATA)
//		{
//			ValueMap row = temp[ENTERROOMDATA].asValueMap();
//			rapidjson::Value v_map(rapidjson::kObjectType);
//
//			rapidjson::Value v_add;
//			v_add.SetBool(row[ADDROOM].asBool());
//			v_map.AddMember(ADDROOM, v_add, allocator);
//
//			rapidjson::Value v_rTag;
//			v_rTag.SetInt(row[ROOMLABEL].asInt());
//			v_map.AddMember(ROOMLABEL, v_rTag, allocator);
//
//			rapidjson::Value v_name;
//			v_name.SetString(row[PLAYERNAME].asString().c_str(), allocator);
//			v_map.AddMember(PLAYERNAME, v_name, allocator);
//
//			object.AddMember(SWAITINGSCENEDATA, v_map, allocator);
//		}
//
//		array.PushBack(object, allocator);
//	}
//
//	//document.AddMember("change", true, allocator);
//	document.AddMember("Record", array, allocator);
//
//	rapidjson::StringBuffer buffer;
//	rapidjson::Writer < rapidjson:: StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里
//
//	document.Accept(writer);	//通过write将数据写入buffer
//	
//	message.setSendBuf(buffer.GetString());
//	//log("out: %s", out);
//}

//or return string
string enJsonParser::encode_WaitingRoomData()
{
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法

	rapidjson::Value v_map(rapidjson::kObjectType);
	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();				//这里的v就是map，Value是一种包装类，可以把很多数据类型包装成类

		ValueMap row = temp[WAITINGSCENEDATA].asValueMap();

		rapidjson::Value v_add;
		v_add.SetBool(row[ADDROOM].asBool());
		v_map.AddMember(ADDROOM, v_add, allocator);

		rapidjson::Value v_rTag;
		v_rTag.SetInt(row[ROOMLABEL].asInt());
		v_map.AddMember(ROOMLABEL, v_rTag, allocator);

		rapidjson::Value v_name;
		v_name.SetString(row[PLAYERNAME].asString().c_str(), allocator);
		v_map.AddMember(PLAYERNAME, v_name, allocator);
	}

	//document.AddMember("change", true, allocator);
	document.AddMember(WAITINGSCENEDATA, v_map, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
	//log("out: %s", out);
}

string enJsonParser::encode_EnterGameData()
{
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法

	rapidjson::Value v_map(rapidjson::kObjectType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();				//这里的v就是map，Value是一种包装类，可以把很多数据类型包装成类

		ValueMap row = temp[ROOMSCENEDATA].asValueMap();

		rapidjson::Value v_sta;
		v_sta.SetBool(row[ISSTART].asBool());
		v_map.AddMember(ISSTART, v_sta, allocator);
	}

	//document.AddMember("change", true, allocator);
	document.AddMember(ROOMSCENEDATA, v_map, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
}

string enJsonParser::encode_MilitaryData()
{
	using namespace encode_MilitaryData;
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法
	//放置object
	rapidjson::Value object(rapidjson::kObjectType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();
		//放置三种兵种的信息
		ValueMap row = temp[MILITARYDATA].asValueMap();

		ValueVector DogData = row[DOGDATA].asValueVector();
		ValueVector SoldierData = row[SOLDIERDATA].asValueVector();
		ValueVector EngineerData = row[ENGINEERDATA].asValueVector();

		rapidjson::Value dog_array(rapidjson::kArrayType);
		rapidjson::Value soldier_array(rapidjson::kArrayType);
		rapidjson::Value engineer_array(rapidjson::kArrayType);

		ValueVector& temp_data = DogData;
		rapidjson::Value& temp_array = dog_array;
		for (int i = Dog_Data; i <= Engineer_Data; ++i)
		{
			if (i == Dog_Data)
			{
				temp_array = dog_array;
				temp_data = DogData;
			}
			else if (i == Soldier_Data)
			{
				temp_array = soldier_array;
				temp_data = SoldierData;
			}
			else if (i == Engineer_Data)
			{
				temp_array = engineer_array;
				temp_data = EngineerData;
			}
			for (auto& dv : temp_data)	//dv为ValueMap代表一个兵的信息
			{
				ValueMap temp_map = dv.asValueMap();
				rapidjson::Value json_map(rapidjson::kObjectType);

				rapidjson::Value v_hp;
				v_hp.SetInt(temp_map[HEALTHPOINT].asInt());
				json_map.AddMember(HEALTHPOINT, v_hp, allocator);

				rapidjson::Value v_px;
				v_px.SetFloat(temp_map[POSITIONX].asFloat());
				json_map.AddMember(POSITIONX, v_px, allocator);

				rapidjson::Value v_py;
				v_py.SetFloat(temp_map[POSITIONY].asFloat());
				json_map.AddMember(POSITIONY, v_py, allocator);

				rapidjson::Value v_dx;
				v_dx.SetFloat(temp_map[DESTINATIONX].asFloat());
				json_map.AddMember(DESTINATIONX, v_dx, allocator);

				rapidjson::Value v_dy;
				v_dy.SetFloat(temp_map[DESTINATIONY].asFloat());
				json_map.AddMember(DESTINATIONY, v_dy, allocator);

				rapidjson::Value v_st;
				v_st.SetString(temp_map[STATUS].asString().c_str(), allocator);
				json_map.AddMember(STATUS, v_st, allocator);

				rapidjson::Value v_ct;
				v_ct.SetInt(temp_map[COUNTRY].asInt());
				json_map.AddMember(COUNTRY, v_ct, allocator);

				rapidjson::Value v_tg;
				v_tg.SetInt(temp_map[STAG].asInt());
				json_map.AddMember(STAG, v_tg, allocator);

				temp_array.PushBack(json_map, allocator);
			}
			if (i == Dog_Data)
			{
				object.AddMember(DOGDATA, temp_array, allocator);
			}
			else if (i == Soldier_Data)
			{
				object.AddMember(SOLDIERDATA, temp_array, allocator);
			}
			else if (i == Engineer_Data)
			{
				object.AddMember(ENGINEERDATA, temp_array, allocator);
			}
		}
	}
	document.AddMember(MILITARYDATA, object, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
}

string enJsonParser::encode_ConstructionData()
{
	using namespace encode_ConstructionData;
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法
																					//放置object																		//放置object
	rapidjson::Value object(rapidjson::kObjectType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();

		ValueMap row = temp[CONSTRUCTIONDATA].asValueMap();

		ValueVector barData = row[BARRACKSDATA].asValueVector();
		ValueVector warData = row[WARFACTORYDATA].asValueVector();
		ValueVector minData = row[MINEDATA].asValueVector();
		ValueVector basData = row[BASEDATA].asValueVector();

		rapidjson::Value bar_array(rapidjson::kArrayType);
		rapidjson::Value war_array(rapidjson::kArrayType);
		rapidjson::Value min_array(rapidjson::kArrayType);
		rapidjson::Value bas_array(rapidjson::kArrayType);

		ValueVector& temp_data = barData;
		rapidjson::Value& temp_array = bar_array;
		for (int i = Bar_Data; i <= Bas_Data; ++i)
		{
			if (i == Bar_Data)
			{
				temp_array = bar_array;
				temp_data = barData;
			}
			else if (i == War_Data)
			{
				temp_array = war_array;
				temp_data = warData;
			}
			else if (i == Min_Data)
			{
				temp_array = min_array;
				temp_data = minData;
			}
			else if (i == Bas_Data)
			{
				temp_array = bas_array;
				temp_data = basData;
			}
			for (auto& dv : temp_data)	//dv为ValueMap代表一个兵的信息
			{
				ValueMap temp_map = dv.asValueMap();
				rapidjson::Value json_map(rapidjson::kObjectType);

				rapidjson::Value v_hp;
				v_hp.SetInt(temp_map[HEALTHPOINT].asInt());
				json_map.AddMember(HEALTHPOINT, v_hp, allocator);

				rapidjson::Value v_px;
				v_px.SetFloat(temp_map[POSITIONX].asFloat());
				json_map.AddMember(POSITIONX, v_px, allocator);

				rapidjson::Value v_py;
				v_py.SetFloat(temp_map[POSITIONY].asFloat());
				json_map.AddMember(POSITIONY, v_py, allocator);

				rapidjson::Value v_ct;
				v_ct.SetInt(temp_map[COUNTRY].asInt());
				json_map.AddMember(COUNTRY, v_ct, allocator);

				rapidjson::Value v_tg;
				v_tg.SetInt(temp_map[STAG].asInt());
				json_map.AddMember(STAG, v_tg, allocator);

				temp_array.PushBack(json_map, allocator);
			}
			if (i == Bar_Data)
			{
				object.AddMember(BARRACKSDATA, temp_array, allocator);
			}
			else if (i == War_Data)
			{
				object.AddMember(WARFACTORYDATA, temp_array, allocator);
			}
			else if (i == Min_Data)
			{
				object.AddMember(MINEDATA, temp_array, allocator);
			}
			else if (i == Bas_Data)
			{
				object.AddMember(BASEDATA, temp_array, allocator);
			}
		}
	}
	document.AddMember(CONSTRUCTIONDATA, object, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
}