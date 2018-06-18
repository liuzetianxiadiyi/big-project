#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "Value.h"
#include <initializer_list>
//这里可以再私有变量中加一个函数指针，通过函数指针来调用不同函数，但是我不能正确赋值

#define WAITINGSCENEDATA "WaitingSceneData"	//Waiting界面发送数据的标识
#define ROOMNUMS "RoomNums"			//房间数量
#define ADDROOM "AddRoom"		//是否添加房间
#define ROOMLABEL "RoomLabel"		//加入的房间的Tag
#define DELETED "Deleted"		//是否删除了房间
#define DELETEDROOM "DeletedRoom"	//删除房间的Tag
#define PLAYERNAME "playername"		//玩家姓名
#define OWNER "owner"		//房主
#define MEMBER "member"		//成员

#define ROOMSCENEDATA "RoomSceneData"		//Room 界面发送数据标识
#define ISSTART "isStart" 

#define SENTERROOMDATA "sEnterRoomData"		//进入游戏

#define MILITARYDATA "MilitaryData"	//兵种信息
#define DOGDATA "DogData"
#define SOLDIERDATA "SoldierData"
#define ENGINEERDATA "EngineerData"
#define HEALTHPOINT "HealhPoint"	//血量
#define DESTINATIONX "destinationX"	//目的地
#define DESTINATIONY "destinationY"
#define POSITIONX "PositionX"		//所在地
#define POSITIONY "positionY"
#define STATUS "Status"	//状态
#define ISFIGHTING "isFighting"
#define ISMOVING "isMoving"
#define NOTHING "nothing"
#define COUNTRY "Country"	//士兵所属国家

#define CONSTRUCTIONDATA "ConstructionData"
#define BARRACKSDATA "BarracksData"
#define WARFACTORYDATA "WarfactoryData"
#define MINEDATA "MineData"
#define BASEDATA "BaseData"

#define SWAITINGSCENEDATA "sWaitingSceneData"		//服务器端
#define SROOMSCENEDATA "sRoomSceneData"

using std::string;
using std::initializer_list;
using std::pair;
using std::make_pair;

namespace encode_MilitaryData
{
	enum
	{
		Dog_Data = 0,
		Soldier_Data,
		Engineer_Data
	};
}

namespace encode_ConstructionData
{
	enum
	{
		Bar_Data = 0,
		War_Data,
		Min_Data,
		Bas_Data
	};
}

class GameData
{
public:
	static ValueVector toValueVector(MyValue value);
	static ValueVector toValueVector(initializer_list<MyValue> il);

	static ValueMap toValueMap(initializer_list<pair<string, MyValue>> il);
	static ValueMap toValueMap(pair<string, MyValue>);

	static pair<string, MyValue> toPair(const char* order, MyValue value);

	static ValueVector WaitingData(bool Add_Value, int Room_Value, string player_Value);

	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted, ValueVector rdeleted);
	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted);

	static ValueVector sRoomData(ValueVector nmember);
};

#endif