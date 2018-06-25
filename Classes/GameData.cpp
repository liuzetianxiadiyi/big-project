#include "GameData.h"

ValueVector GameData::toValueVector(initializer_list<Value> il)
{
	cocos2d::ValueVector plistdata;
	for (Value value : il)
	{
		plistdata.push_back(value);
	}

	return plistdata;
}

ValueVector GameData::toValueVector(Value value)
{
	cocos2d::ValueVector plistdata;
	plistdata.push_back(value);
	return plistdata;
}

ValueMap GameData::toValueMap(initializer_list<pair<string, Value>> il)
{
	cocos2d::ValueMap valuemap;
	for (pair<string, Value> Pair : il)
	{
		valuemap.insert(Pair);
	}

	return valuemap;
}

ValueMap GameData::toValueMap(pair<string, Value> Pair)
{
	cocos2d::ValueMap valuemap;
	valuemap.insert(Pair);
	return valuemap;
}

pair<string, Value> GameData::toPair(const char * order, Value value)
{
	return make_pair(string(order), value);
}

ValueVector GameData::WaitingData(bool Add_Value, int Room_Value, string Player_Value)
{
	pair<string, Value> temp_pair0 = make_pair(ADDROOM, Value(Add_Value));
	pair<string, Value> temp_pair1 = make_pair(ROOMLABEL, Value(Room_Value));
	pair<string, Value> temp_pair2 = make_pair(PLAYERNAME, Value(Player_Value));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2 });
	pair<string, Value> temp_pair = make_pair(WAITINGSCENEDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sWaitngData(int addroom, ValueVector rLable, bool deleted, ValueVector rdeleted)
{
	pair<string, Value> temp_pair0 = make_pair(ADDROOM, Value(addroom));
	pair<string, Value> temp_pair1 = make_pair(ROOMLABEL, Value(rLable));
	pair<string, Value> temp_pair2 = make_pair(DELETED, Value(deleted));
	pair<string, Value> temp_pair3 = make_pair(DELETEDROOM, Value(rdeleted));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2,temp_pair3 });
	pair<string, Value> temp_pair = make_pair(SWAITINGSCENEDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sWaitngData(int addroom, ValueVector rLable, bool deleted)
{
	pair<string, Value> temp_pair0 = make_pair(ADDROOM, Value(addroom));
	pair<string, Value> temp_pair1 = make_pair(ROOMLABEL, Value(rLable));
	pair<string, Value> temp_pair2 = make_pair(DELETED, Value(deleted));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2 });
	pair<string, Value> temp_pair = make_pair(SWAITINGSCENEDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::RoomData(bool start)
{
	pair<string, Value> temp_pair0 = make_pair(ISSTART, Value(start));

	ValueMap temp_map = GameData::toValueMap(temp_pair0);
	pair<string, Value> temp_pair = make_pair(ROOMSCENEDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sRoomData(ValueVector nmember)
{
	//pair<string, Value> temp_pair0 = make_pair(OWNER, Value(nowner));
	pair<string, Value> temp_pair0 = make_pair(MEMBER, Value(nmember));

	ValueMap temp_map = GameData::toValueMap(temp_pair0);
	pair<string, Value> temp_pair = make_pair(SROOMSCENEDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::MilitaryData(vector<Military*> il)

{

	ValueVector DogData;

	//int DogCount = 0;

	ValueVector SoldierData;

	//int SoliderCount = 0;

	ValueVector EngineerData;

	//int EngineerCount = 0;



	for (auto v : il)

	{

		pair<string, Value> temp_pair0 = make_pair(HEALTHPOINT, Value(v->gethp()));

		pair<string, Value> temp_pair1 = make_pair(POSITIONX, Value(v->getPositionX()));

		pair<string, Value> temp_pair2 = make_pair(POSITIONY, Value(v->getPositionY()));

		pair<string, Value> temp_pair3 = make_pair(DESTINATIONX, Value(v->getDestination().x));

		pair<string, Value> temp_pair4 = make_pair(DESTINATIONY, Value(v->getDestination().y));

		pair<string, Value> temp_pair5 = make_pair(STATUS, Value(v->getStatus()));

		pair<string, Value> temp_pair6 = make_pair(COUNTRY, Value(v->getCountry()));

		pair<string, Value> temp_pair7 = make_pair(STAG, Value(v->getTag()));

		ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2,temp_pair3,temp_pair4,temp_pair5,temp_pair6 });

		if (typeid(v) == typeid(Dog))

		{

			DogData.push_back(Value(temp_map));

		}

		else if (typeid(v) == typeid(Soldier))

		{

			SoldierData.push_back(Value(temp_map));

		}

		else if (typeid(v) == typeid(Engineer))

		{

			EngineerData.push_back(Value(temp_map));

		}

	}

	pair<string, Value> dog_pair = make_pair(DOGDATA, Value(DogData));

	pair<string, Value> Soldier_pair = make_pair(SOLDIERDATA, Value(SoldierData));

	pair<string, Value> Engineer_pair = make_pair(ENGINEERDATA, Value(EngineerData));

	ValueMap MilitaryMap = GameData::toValueMap({ dog_pair,Soldier_pair,Engineer_pair });

	return GameData::toValueVector(Value(GameData::toValueMap(make_pair(MILITARYDATA, Value(MilitaryMap)))));

}



ValueVector GameData::ConstructionData(vector<Construction*> il)

{

	ValueVector BarracksData;

	ValueVector WarfactoryData;

	ValueVector MineData;

	ValueVector BaseData;



	for (auto v : il)

	{

		pair<string, Value> temp_pair0 = make_pair(HEALTHPOINT, Value(v->gethp()));

		pair<string, Value> temp_pair1 = make_pair(POSITIONX, Value(v->getPositionX()));

		pair<string, Value> temp_pair2 = make_pair(POSITIONY, Value(v->getPositionY()));

		pair<string, Value> temp_pair3 = make_pair(COUNTRY, Value(v->getCountry()));

		ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2,temp_pair3 });

		if (typeid(v) == typeid(Barracks))

		{

			BarracksData.push_back(Value(temp_map));

		}

		else if (typeid(v) == typeid(Warfactory))

		{

			WarfactoryData.push_back(Value(temp_map));

		}

		else if (typeid(v) == typeid(Mine))

		{

			MineData.push_back(Value(temp_map));

		}

		else if (typeid(v) == typeid(Base))

		{

			BaseData.push_back(Value(temp_map));

		}

	}



	pair<string, Value> Barracks_pair = make_pair(BARRACKSDATA, Value(BarracksData));

	pair<string, Value> Warfactory_pair = make_pair(WARFACTORYDATA, Value(WarfactoryData));

	pair<string, Value> Mine_pair = make_pair(MINEDATA, Value(MineData));

	pair<string, Value> Base_pair = make_pair(BASEDATA, Value(BaseData));

	ValueMap ConstructionMap = GameData::toValueMap({ Barracks_pair ,Warfactory_pair ,Mine_pair ,Base_pair });

	return GameData::toValueVector(Value(GameData::toValueMap(make_pair(CONSTRUCTIONDATA, Value(ConstructionMap)))));

}