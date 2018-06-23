#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __SERVER_H__
#define __SERVER_H__

//服务器		由服务器主机运行
#include <WinSock2.h>	//socket 所需文件
#pragma comment(lib,"WS2_32.lib")	// link socket 库
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "sJsonParser.h"
#include "senJsonParser.h"

#define PORT 9999
#define TIME_LAG 500		//发送和接收信息的时间间隔
#define WAITTIME 100		//发送失败后等待时间
#define TIMEOUTERROR 5000	//超时时间
#define BUFLEN 1024
#define MAXCLIENTS 8

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
//不使用构造和析构函数

//recursive_mutex rmtx;
using namespace std;

class Server
{
private:

	WSADATA wsaData;
	SOCKET sServer;
	SOCKADDR_IN addrServer;
	//need lock
	vector<SOCKET> wClients;
	//need lock
	unordered_map<int,vector<SOCKET>>  rClients;
	unordered_map<int, vector<string>> rClient_names;
	//neeed lock
	unordered_map<int, SOCKET> rOwner;
	vector<vector<SOCKET>> gameClients;

	//need lock
	// WaitingData;
	int addroom;
	ValueVector vLabel;
	bool deleted;
	ValueVector dLabel;

	recursive_mutex waitingLock;
	recursive_mutex OwnerLock;
	recursive_mutex RoomLock;
	recursive_mutex GameLock;
public:
	bool init();
	Server();
	~Server();

	BOOL AcceptClients();
	BOOL send_Ser(SOCKET sClient,string message);

	void RoomNums_Data_Thread();
	void EnterGame_Data_Thread();
	void GameData_Thread();

	//vector<SOCKET>& GetwClients();
	//vector<vector<SOCKET>>& GetClient_inGame_Vector();
	//unordered_map<int, Room_Client>& GetrClients();
};

#endif