#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __SERVER_H__
#define __SERVER_H__

//������		�ɷ�������������
#include <WinSock2.h>	//socket �����ļ�
#pragma comment(lib,"WS2_32.lib")	// link socket ��
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "sJsonParser.h"
#include "senJsonParser.h"

#define PORT 9999
#define TIME_LAG 10		//���ͺͽ�����Ϣ��ʱ����
#define WAITTIME 100		//����ʧ�ܺ�ȴ�ʱ��
#define TIMEOUTERROR 5000	//��ʱʱ��
#define BUFLEN 1024
#define MAXCLIENTS 8
#define RECIEVE "recieve"

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
//��ʹ�ù������������

//recursive_mutex rmtx;
using namespace std;

struct SocketWithFlag
{
	SOCKET client;
	bool isDeleted;

	SocketWithFlag(SOCKET c, bool d)
	{
		client = c;
		isDeleted = d;
	}
	SocketWithFlag()
	{
		client = NULL;
	}
};

class Server
{
private:

	WSADATA wsaData;
	SOCKET sServer;
	SOCKADDR_IN addrServer;
	//need lock
	vector<SocketWithFlag> wClients;
	//need lock
	unordered_map<int,vector<SocketWithFlag>>  rClients;
	unordered_map<int, vector<string>> rClient_names;
	//neeed lock
	unordered_map<int, SocketWithFlag> rOwner;
	vector<vector<SocketWithFlag>> gameClients;
	int room_nums;
	ValueVector roomTag;
	//need lock
	// WaitingData;
	int addroom;
	ValueVector vLabel;
	bool deleted;
	ValueVector dLabel;

	bool thread_end;

	recursive_mutex waitingDataLock;
	recursive_mutex wVectorLock;
	recursive_mutex OwnerLock;
	recursive_mutex RoomLock;
	recursive_mutex GameLock;
public:
	bool init();
	Server();
	~Server();

	bool sSend(string sendBuf,SocketWithFlag client,char recvBuf[]);
	bool sRecv(SocketWithFlag client);

	BOOL AcceptClients();
	void RoomNums_Data_Thread();
	void EnterGame_Data_Thread();
	void GameData_Thread();

	//vector<SOCKET>& GetwClients();
	//vector<vector<SOCKET>>& GetClient_inGame_Vector();
	//unordered_map<int, Room_Client>& GetrClients();
};

#endif