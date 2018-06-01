#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "cocos2d.h"
#include "SystemHeader.h"

#include <initializer_list>
#include <mutex>
//���������˽�б����м�һ������ָ�룬ͨ������ָ�������ò�ͬ�����������Ҳ�����ȷ��ֵ
USING_NS_CC;

#define WAITINGSCENEDATA "WaitingSceneData"	//Waiting���淢�����ݵı�ʶ
#define ROOMNUMS "RoomNums"			//��������
#define ADDROOM "AddRoom"		//�Ƿ���ӷ���
#define ROOMLABEL "RoomLabel"		//����ķ����Tag
#define DELETED "Deleted"		//�Ƿ�ɾ���˷���
#define DELETEDROOM "DeletedRoom"	//ɾ�������Tag
#define PLAYERNAME "playername"		//�������
#define OWNER "owner"		//����
#define MEMBER "member"		//��Ա

#define ROOMSCENEDATA "RoomSceneData"		//Room ���淢�����ݱ�ʶ
#define ISSTART "isStart" 

#define SENTERROOMDATA "sEnterRoomData"		//������Ϸ

#define MILITARYDATA "MilitaryData"	//������Ϣ
#define DOGDATA "DogData"
#define SOLDIERDATA "SoldierData"
#define ENGINEERDATA "EngineerData"
#define HEALTHPOINT "HealhPoint"	//Ѫ��
#define DESTINATIONX "destinationX"	//Ŀ�ĵ�
#define DESTINATIONY "destinationY"
#define POSITIONX "PositionX"		//���ڵ�
#define POSITIONY "positionY"
#define STATUS "Status"	//״̬
#define ISFIGHTING "isFighting"
#define ISMOVING "isMoving"
#define NOTHING "nothing"
#define COUNTRY "Country"	//ʿ����������

#define CONSTRUCTIONDATA "ConstructionData"
#define BARRACKSDATA "BarracksData"
#define WARFACTORYDATA "WarfactoryData"
#define MINEDATA "MineData"
#define BASEDATA "BaseData"

#define SWAITINGSCENEDATA "sWaitingSceneData"		//��������
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
	static ValueVector toValueVector(Value value);
	static ValueVector toValueVector(initializer_list<Value> il);

	static ValueMap toValueMap(initializer_list<pair<string, Value>> il);
	static ValueMap toValueMap(pair<string, Value>);

	static pair<string, Value> toPair(const char* order, Value value);

	static ValueVector WaitingData(bool Add_Value, int Room_Value, string player_Value);
	static ValueVector MilitaryData(initializer_list<Military*> il);
	static ValueVector ConstructionData(initializer_list<Construction*> il);


	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted, ValueVector rdeleted);
	static ValueVector sWaitngData(int addroom, ValueVector rLable, bool deleted);
	//���������յ�������Ϣʱ������һ����������Tag��������������������Ӧ����ݵ�ValueVector��
	//ÿһ��ΪValueMap������Ԫ�طֱ�Ϊ<string,int>,ValueMap<identity,name>,Tag�����д���
	static ValueVector sRoomData(string nowner, ValueVector nmember);
};

#endif