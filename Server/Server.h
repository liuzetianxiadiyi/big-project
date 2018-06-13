#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __SERVER_H__
#define __SERVER_H__

//服务器		由服务器主机运行
#include "WinSock2.h"	//socket 所需文件
#pragma comment(lib,"WS2_32.lib")	// link socket 库
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "cocos2d.h"
USING_NS_CC;
#include "Information.h"
#include "Client_Vector.h"
#include "sJsonParser.h"

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

recursive_mutex rmtx;
using namespace std;

class Server
{
private:
	WSADATA wsaData;
	SOCKET sServer;
	SOCKADDR_IN addrServer;

	vector<SOCKET> wClients;
	unordered_map<int,vector<SOCKET>>  rClients;
	unordered_map<int, vector<string>> rClient_names;
	unordered_map<int, SOCKET> rOwner;
	vector<vector<SOCKET>> gameClients;

	//Information information;
	//string Room_Nums_Data;
	ValueVector WaitingData;
public:
	bool init();
	Server();
	~Server();

	BOOL AcceptClients();
	BOOL recv_Ser(SOCKET sClient);
	BOOL send_Ser(SOCKET sClient,string message);

	void RoomNums_Data_Thread();
	void EnterGame_Data_Thread();
	void GameData_Thread();

	/*vector<SOCKET>& GetwClients();
	vector<vector<SOCKET>>& GetClient_inGame_Vector();
	unordered_map<int, Room_Client>& GetrClients();*/
};

#endif