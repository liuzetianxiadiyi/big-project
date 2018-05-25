#include "GameData.h"
#include "WaitingScene.h"

using std::make_pair;

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

ValueVector GameData::WaitingData(bool Add_Value, int Room_value, string Player_Value)
{
	pair<string, Value> temp_pair0 = make_pair(ADDROOM, Value(Add_Value));
	pair<string, Value> temp_pair1 = make_pair(ROOMLABEL, Value(Room_value));
	pair<string, Value> temp_pair2 = make_pair(PLAYERNAME, Value(Player_Value));
	ValueMap temp_map = GameData::toValueMap({ temp_pair0,temp_pair1,temp_pair2 });
	pair<string, Value> temp_pair = make_pair(ENTERROOMDATA, Value(temp_map));
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(temp_pair)));

	return plistdata;
}