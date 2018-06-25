#include "senJsonParser.h"

senJsonParser::senJsonParser(ValueVector pListData)
{
	listData = pListData;
}
string senJsonParser::encode_WaitingData()		//这里换成message防止直接使用全局变量information造成未知的bug
{
	Json::Value object(Json::objectValue);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();

		ValueMap row = temp[SWAITINGSCENEDATA].asValueMap();
		Json::Value v_map;

		v_map[ADDROOM] = row[ADDROOM].asInt();

		Json::Value v_rTag(Json::arrayValue);
		ValueVector TagVector = row[ROOMLABEL].asValueVector();
		for (auto& tv : TagVector)
		{
			v_rTag.append(tv.asInt());
		}
		v_map[ROOMLABEL] = v_rTag;

		v_map[DELETED] = row[DELETED].asBool();

		if (row[DELETED].asBool())
		{
			Json::Value v_dTag(Json::arrayValue);
			ValueVector dTagVector = row[DELETEDROOM].asValueVector();
			for (auto& dv : dTagVector)
			{
				v_dTag.append(dv.asInt());
			}
			v_map[DELETEDROOM] = v_dTag;
		}

		object[SWAITINGSCENEDATA] = v_map;
	}

	return object.toStyledString();
	//log("out: %s", out);
}

string senJsonParser::encode_RoomData()		//这里换成message防止直接使用全局变量information造成未知的bug
{
	Json::Value object(Json::objectValue);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();

		ValueMap row = temp[SROOMSCENEDATA].asValueMap();
		Json::Value v_map(Json::arrayValue);

		/*rapidjson::Value v_own;
		v_own.SetString(row[OWNER].asString().c_str(), allocator);
		v_map.AddMember(OWNER, v_own, allocator);*/

		Json::Value aname(Json::arrayValue);
		ValueVector names = row[MEMBER].asValueVector();
		for (auto &nv : names)
		{
			aname.append(nv.asString());
		}
		v_map[MEMBER] = aname;

		object[SROOMSCENEDATA] = v_map;
	}

	return object.toStyledString();
	//log("out: %s", out);
}


string senJsonParser::encode_EnterData()
{
	Json::Value object(Json::objectValue);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();				//这里的v就是map，Value是一种包装类，可以把很多数据类型包装成类

		ValueMap row = temp[SROOMSCENEDATA].asValueMap();
		Json::Value v_map(Json::arrayValue);

		v_map[ISSTART] = row[ISSTART].asBool();

		object[SROOMSCENEDATA] = v_map;
	}

	return object.toStyledString();
}

string senJsonParser::encode_aRoomData()
{
	Json::Value object(Json::objectValue);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();	

		object[ADDNAME] = temp[ADDNAME].asString();
	}

	return object.toStyledString();
}
/*
string senJsonParser::encode_MilitaryData()
{
	using namespace encode_MilitaryData;
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法
																					//放置object																		//放置object
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();
		//放置三种兵种的信息
		rapidjson::Value dobject(rapidjson::kObjectType);
		rapidjson::Value object(rapidjson::kObjectType);
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

				temp_array.PushBack(temp_map, allocator);
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
		dobject.AddMember(MILITARYDATA, object, allocator);
		array.PushBack(dobject, allocator);
	}
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
}

string senJsonParser::encode_ConstructionData()
{
	using namespace encode_ConstructionData;
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法
																					//放置object																		//放置object
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto& v : listData)
	{
		ValueMap temp = v.asValueMap();

		rapidjson::Value dobject(rapidjson::kObjectType);
		rapidjson::Value object(rapidjson::kObjectType);
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

				temp_array.PushBack(temp_map, allocator);
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
		dobject.AddMember(CONSTRUCTIONDATA, object, allocator);
		array.PushBack(dobject, allocator);
	}
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson::StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer

	return string(buffer.GetString());
}*/