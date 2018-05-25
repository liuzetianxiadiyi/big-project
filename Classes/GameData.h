#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "cocos2d.h"
#include "SystemHeader.h"

#include <initializer_list>
#include <mutex>
//这里可以再私有变量中加一个函数指针，通过函数指针来调用不同函数，但是我不能正确赋值
USING_NS_CC;

#define WAITINGSCENEDATA "WaitingSceneData"
#define ROOMNUMS "RoomNums"
#define ADDROOM "AddRoom"
#define ROOMLABEL "RoomLabel"
#define DELETED "Deleted"
#define DELETEDROOM "DeletedRoom"

#define ENTERROOMDATA "EnterRoomData"
#define ADDROOMDATA "AddRoomData"
#define PLAYERNAME "playername"

#define SWAITINGSCENEDATA "sWaitingSceneData"
#define ROOMMATE "RoomMate"

using std::string;
using std::initializer_list;
using std::pair;

class GameData
{
public:
	static ValueVector toValueVector(Value value);
	static ValueVector toValueVector(initializer_list<Value> il);

	static ValueMap toValueMap(initializer_list<pair<string, Value>> il);
	static ValueMap toValueMap(pair<string, Value>);

	static pair<string, Value> toPair(const char* order, Value value);

	static ValueVector WaitingData(bool Add_Value, int Room_value, string player_value);
};

#endif