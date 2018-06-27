#include "Server.h"
#include <ctime>
#include "senJsonParser.h"
#include "sJsonParser.h"
#include "GameData.h"
#include <string>
using std::cout;
Server::Server()
{
	addroom = 0;
	deleted = false;
	room_nums = 0;
	thread_end = true;
	int create = init();
	//log("create %d", create);
}

bool Server::init()		//如果init返回False，用return退出程序
{
	//num_Clients = 0;
	// 启动并初始化winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}
	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}

	//设置套接字非阻塞模式 
	unsigned long ul = 1;
	if (SOCKET_ERROR == ioctlsocket(sServer, FIONBIO, (unsigned long*)&ul))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	// 准备通信地址
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = INADDR_ANY; //本机任意可用网络地址

	if (SOCKET_ERROR == ::bind(sServer, (const sockaddr*)&addrServer, sizeof(SOCKADDR_IN)))		//使用::bind避免命名冲突
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	//listen
	if (SOCKET_ERROR == listen(sServer, SOMAXCONN))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}
	//等待客户端连接
	return TRUE;
}

bool Server::sSend(string sendBuf,SocketWithFlag client,char recvBuf[])
{
	if (SOCKET_ERROR == send(client.client, sendBuf.c_str(), sendBuf.length(), 0))
	{
		client.isDeleted = true;
		cout << "send error for " <<sendBuf<< endl;
		return false;
	}
	while (true)
	{
		if (SOCKET_ERROR == recv(client.client, recvBuf, BUFLEN, 0))
		{
			//cout << "in recieve!" << endl;
			continue;
		}
		else
		{
			if (string(recvBuf) == string(RECIEVE))
			{
				cout << "client return!" << endl;
				return true;
			}
			cout << "message error" << endl;
			return false;
		}
	}
}

bool Server::sRecv(SocketWithFlag client)
{
	if (SOCKET_ERROR == send(client.client, RECIEVE, sizeof(RECIEVE), 0))
	{
		client.isDeleted = true;
		cout << "send error for recieve" << endl;
		return false;
	}
	return true;
}

BOOL Server::AcceptClients()
{
	sockaddr_in addrClient;
	SOCKET sClient;
	while (true)
	{
		memset(&addrClient, 0, sizeof(sockaddr_in));
		int addrClientLen = sizeof(addrClient);

		//printf("waitting to connect\n");

		sClient = accept(sServer, (sockaddr *)&addrClient, &addrClientLen);
		if (INVALID_SOCKET != sClient)
		{
			printf("connect %s\n", inet_ntoa(addrClient.sin_addr));
			waitingDataLock.lock();

			senJsonParser Json = senJsonParser(GameData::RoomNumsData(room_nums, roomTag));
			waitingDataLock.unlock();
			string sendBuf = Json.encode_RoonNums();
			cout <<"first sendBuf=" <<sendBuf << endl;
			char recvBuf[BUFLEN];
			ZeroMemory(recvBuf,sizeof(recvBuf));
			if (sSend(sendBuf, SocketWithFlag(sClient, false),recvBuf))
			{
				wVectorLock.lock();
				wClients.push_back(SocketWithFlag(sClient, false));
				wVectorLock.unlock();
				printf("send success\n");
			}
		}
		Sleep(TIME_LAG);
	}
	//++num_Clients;
	return TRUE;
}

void Server::EnterGame_Data_Thread()
{
	while (true)
	{
		//rmtx.lock();
		char recvBuf[BUFLEN];
		char recvBuf2[BUFLEN];
		OwnerLock.lock();
		for (auto it = rOwner.begin(); it != rOwner.end(); ++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			ZeroMemory(recvBuf2, sizeof(recvBuf2));
			//if recieve message,according to the messge put client in waitingvector or gamevector respectively
			//and then erase them in roomvector
			if (SOCKET_ERROR != recv(it->second.client, recvBuf, BUFLEN, 0))
			{
				RoomLock.lock();
				for (auto rc : rClients[it->first])
				{
					if (!sSend(recvBuf,rc, recvBuf2))
					{
						printf("send enter data false for %d\n", rc);
					}
				}
				//put roomClient in gameClient
				sJsonParser json = sJsonParser(recvBuf);
				if (json.decode_RoomData())
				{
					//将room中一个vector中的客户端全部加入gameClient
					GameLock.lock();
					gameClients.push_back(rClients[it->first]);
					GameLock.lock();
				}
				else
				{
					waitingDataLock.lock();
					deleted = true;
					dLabel.push_back(MyValue(it->first));
					wVectorLock.lock();
					wClients.insert(wClients.end(), rClients[it->first].begin(), rClients[it->first].end());
					wVectorLock.unlock();
					waitingDataLock.unlock();
				}
				rClients[it->first].clear();
				RoomLock.unlock();
				it->second.isDeleted = true;
			}
		}
		for (auto it = rOwner.begin(); it != rOwner.end(); ++it)
		{
			if (it->second.isDeleted)
			{
				rOwner.erase(it--);
			}
		}

		OwnerLock.unlock();

		Sleep(TIME_LAG);
	}
}

void Server::RoomNums_Data_Thread()
{
	cout << "in RoomNumsData" << endl;
	while (true)
	{
		//added room label vector
		ValueVector PlayerName;
		char recvBuf[BUFLEN];
		wVectorLock.lock();
		waitingDataLock.lock();
		senJsonParser eJson = senJsonParser(GameData::sWaitngData(addroom, vLabel, deleted, dLabel));
		waitingDataLock.unlock();
		string sendBuf = eJson.encode_WaitingData();
		for (auto it = wClients.begin(); it != wClients.end(); ++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			if (sSend(sendBuf,*it,recvBuf))
			{
				cout << "client return recieve" << endl;
				continue;
			}
			else
			{
				cout << "in RoomNumsData recv succsses " << "message :" << recvBuf << endl;
				sJsonParser json = sJsonParser(recvBuf);

				json.decode_WaitingData();

				string pName = json.getRow()[PLAYERNAME].asString();
				int rLabel = json.getRow()[ROOMLABEL].asInt();

				//put this client in owner or not and room vector
				//add his name in name vector
				if ((json.getRow()[ADDROOM].asBool()))
				{
					//记录数据用于Accept线程数据发送
					++addroom;
					vLabel.push_back(MyValue(rLabel));
					//add in owner vector;
					OwnerLock.lock();
					rOwner[rLabel] = *it;
					OwnerLock.unlock();

					RoomLock.lock();
					rClients[rLabel].push_back(*it);
					RoomLock.unlock();
				}
				else
				{
					//send playername message
					for (auto s : rClient_names[rLabel])
					{
						PlayerName.push_back(MyValue(s));
					}
					senJsonParser enJson = senJsonParser(GameData::sRoomData(PlayerName));
					string sendBuf = enJson.encode_RoomData();
					//传输已有玩家姓名
					ZeroMemory(recvBuf, sizeof(recvBuf));
					if (!sSend(sendBuf, *it,recvBuf))
					{
						printf("send room data false \n");
					}
					RoomLock.lock();
					//传输新加入玩家姓名
					for (auto& c : rClients[rLabel])
					{
						senJsonParser _enJson = senJsonParser(GameData::toValueVector(MyValue(GameData::toValueMap(make_pair(ADDROOM, MyValue(pName))))));
						string _sendBuf = _enJson.encode_aRoomData();
						ZeroMemory(recvBuf, sizeof(recvBuf));
						if (!sSend(_sendBuf, *it,recvBuf))
						{
							printf("send room data false\n");
						}
					}
					rClients[rLabel].push_back(*it);
					RoomLock.unlock();
				}
				rClient_names[rLabel].push_back(pName);
				it->isDeleted = true;
			}
		}
		for (auto it = wClients.begin(); it != wClients.end();)
		{
			if (it->isDeleted)
			{
				it = wClients.erase(it);
			}
			else
			{
				++it;
			}
		}

		addroom = 0;
		//cout << "in RoomNumsData waiting lock" << endl;
		for (auto it = wClients.begin(); it != wClients.end(); ++it)
		{

		}

		waitingDataLock.lock();
		room_nums += addroom;
		waitingDataLock.unlock();
		for (auto it = wClients.begin(); it != wClients.end(); ++it)
		{
			if (it->isDeleted)
			{
				wClients.erase(it--);
			}
		}
		wVectorLock.unlock();
		
		Sleep(TIME_LAG);

	}
}

void Server::GameData_Thread()
{
	char recvBuf[BUFLEN];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	char recvBuf2[BUFLEN];
	ZeroMemory(recvBuf2, sizeof(recvBuf2));
	while (true)
	{
		GameLock.lock();
		for (auto cs : gameClients)
		{
			string information;
			for (auto c : cs)
			{
				ZeroMemory(recvBuf, sizeof(recvBuf));
				if (SOCKET_ERROR != recv(c.client, recvBuf, sizeof(recvBuf), 0))
				{
					for (auto _c : cs)
					{
						if (_c.client != c.client)
						{
							if (SOCKET_ERROR == send(_c.client, recvBuf, BUFLEN, 0))
							{
								printf("GameData send false for %d\n", _c.client);
								_c.isDeleted = true;
							}
						}
					}
				}
			}
		}
		GameLock.unlock();
		//rmtx.unlock();
		Sleep(TIME_LAG);
	}

}

//发送数据,超出五秒则不再发送


Server::~Server()
{
	closesocket(sServer);
	WSACleanup();
}