#include "GameData.h"
#include "Value.h"
ValueVector GameData::toValueVector(initializer_list<MyValue> il)
{
	ValueVector plistdata;
	for (MyValue value : il)
	{
		plistdata.push_back(value);
	}

	return plistdata;
}

ValueVector GameData::toValueVector(MyValue value)
{
	ValueVector plistdata;
	plistdata.push_back(value);
	return plistdata;
}

ValueMap GameData::toValueMap(initializer_list<pair<string, MyValue>> il)
{
	ValueMap valuemap;
	for (pair<string, MyValue> Pair : il)
	{
		valuemap.insert(Pair);
	}

	return valuemap;
}

ValueMap GameData::toValueMap(pair<string, MyValue> Pair)
{
	ValueMap valuemap;
	valuemap.insert(Pair);
	return valuemap;
}

pair<string, MyValue> GameData::toPair(const char * order, MyValue value)
{
	return make_pair(string(order), value);
}

ValueVector GameData::WaitingData(bool Add_Value, int Room_Value, string Player_Value)
{
	pair<string, MyValue> temp_pair0 = make_pair(ADDROOM, MyValue(Add_Value));
	pair<string, MyValue> temp_pair1 = make_pair(ROOMLABEL, MyValue(Room_Value));
	pair<string, MyValue> temp_pair2 = make_pair(PLAYERNAME, MyValue(Player_Value));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2 });
	pair<string, MyValue> temp_pair = make_pair(WAITINGSCENEDATA, MyValue(temp_map));
	ValueVector plistdata = GameData::toValueVector(MyValue(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sWaitngData(int addroom, ValueVector rLable, bool deleted, ValueVector rdeleted)
{
	pair<string, MyValue> temp_pair0 = make_pair(ADDROOM, MyValue(addroom));
	pair<string, MyValue> temp_pair1 = make_pair(ROOMLABEL, MyValue(rLable));
	pair<string, MyValue> temp_pair2 = make_pair(DELETED, MyValue(deleted));
	pair<string, MyValue> temp_pair3 = make_pair(DELETEDROOM, MyValue(rdeleted));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2,temp_pair3 });
	pair<string, MyValue> temp_pair = make_pair(SWAITINGSCENEDATA, MyValue(temp_map));
	ValueVector plistdata = GameData::toValueVector(MyValue(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sWaitngData(int addroom, ValueVector rLable, bool deleted)
{
	pair<string, MyValue> temp_pair0 = make_pair(ADDROOM, MyValue(addroom));
	pair<string, MyValue> temp_pair1 = make_pair(ROOMLABEL, MyValue(rLable));
	pair<string, MyValue> temp_pair2 = make_pair(DELETED, MyValue(deleted));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2 });
	pair<string, MyValue> temp_pair = make_pair(SWAITINGSCENEDATA, MyValue(temp_map));
	ValueVector plistdata = GameData::toValueVector(MyValue(GameData::toValueMap(temp_pair)));

	return plistdata;
}

ValueVector GameData::sRoomData(ValueVector nmember)
{
	//pair<string, Value> temp_pair0 = make_pair(OWNER, Value(nowner));
	pair<string, MyValue> temp_pair0 = make_pair(MEMBER, MyValue(nmember));

	ValueMap temp_map = GameData::toValueMap(temp_pair0);
	pair<string, MyValue> temp_pair = make_pair(SROOMSCENEDATA, MyValue(temp_map));
	ValueVector plistdata = GameData::toValueVector(MyValue(GameData::toValueMap(temp_pair)));

	return plistdata;
}