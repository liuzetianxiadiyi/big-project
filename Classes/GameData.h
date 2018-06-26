#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "cocos2d.h"
#include <initializer_list>
#include <vector>
#include"Soldiers.h"
#include"Constructions.h"
#include "Military.h"
#include "Construction.h"
//这里可以再私有变量中加一个函数指针，通过函数指针来调用不同函数，但是我不能正确赋值
USING_NS_CC;
using std::vector;

#define WAITINGSCENEDATA "WaitingSceneData"	//Waiting界面发送数据的标识
#define ROOMNUMS "RoomNums"			//房间数量
#define ADDROOM "AddRoom"		//是否添加房间
#define ROOMLABEL "RoomLabel"		//加入的房间的Tag
#define DELETED "Deleted"		//是否删除了房间
#define DELETEDROOM "DeletedRoom"	//删除房间的Tag
#define PLAYERNAME "playername"		//玩家姓名
#define ADDNAME "addName"  //加入玩家的姓名
#define OWNER "owner"		//房主
#define MEMBER "member"		//成员

#define ROOMSCENEDATA "RoomSceneData"		//Room 界面发送数据标识
#define SROOMNUMSDTATA "sRoomNumsData"
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
#define POSITIONY "PositionY"
#define STATUS "Status"	//状态
#define STAG "SpriteTag"	//精灵标签
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

namespace MemberTagInRoom
{
	enum
	{
		Player1 = 1000,
		Player2,
		Player3,
		Player4
	};
}

namespace RoomMessage
{
	enum
	{
		AddMember = -1,
		DeleteRoom = 0,
		StartGame = 1
	};
}

class GameData
{
public:
	static ValueVector toValueVector(Value value);
	static ValueVector toValueVector(initializer_list<Value> il);

	static ValueMap toValueMap(initializer_list<pair<string, Value>> il);
	static ValueMap toValueMap(pair<string, Value>);

	static pair<string, Value> toPair(const char* order, Value value);

	static ValueVector WaitingData(bool Add_Value, int Room_Value, string player_Value);
	static ValueVector RoomData(bool start);

	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted, ValueVector rdeleted);
	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted);

	static ValueVector sRoomData(ValueVector nmember);
	static ValueVector ConstructionData(vector<Construction*> il);
	static ValueVector MilitaryData(vector<Military*> il);
};

#endif