#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "Value.h"
#include <initializer_list>
//���������˽�б����м�һ������ָ�룬ͨ������ָ�������ò�ͬ�����������Ҳ�����ȷ��ֵ

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