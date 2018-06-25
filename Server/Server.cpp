#include "Server.h"
#include <ctime>
#include "senJsonParser.h"
#include "sJsonParser.h"
#include "GameData.h"

Server::Server()
{
	addroom = 0;
	deleted = false;
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
			//printf("connect %s\n", inet_ntoa(addrClient.sin_addr));
			waitingLock.lock();
			wClients.push_back(sClient);

			senJsonParser Json = senJsonParser(GameData::sWaitngData(addroom, vLabel, deleted, dLabel));
			waitingLock.unlock();
			string sendBuf = Json.encode_WaitingData();
			cout << sendBuf << endl;
			if (SOCKET_ERROR == send(sClient, sendBuf.c_str(), sendBuf.length(), 0))
			{
				printf("send waiting data false for %s\n", inet_ntoa(addrClient.sin_addr));
			}
		}
		//printf("end\n");
		//Sleep(TIME_LAG);
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
		vector < unordered_map<int, SOCKET>::iterator> deleteds;
		OwnerLock.lock();
		for (unordered_map<int, SOCKET>::iterator it = rOwner.begin();it!=rOwner.end();++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			//if recieve message,according to the messge put client in waitingvector or gamevector respectively
			//and then erase them in roomvector
			if (SOCKET_ERROR != recv(it->second, recvBuf, BUFLEN, 0))
			{
				RoomLock.lock();
				for (auto rc : rClients[it->first])
				{
					if (SOCKET_ERROR == send(rc, recvBuf, sizeof(recvBuf), 0))
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
					waitingLock.lock();
					wClients.insert(wClients.end(), rClients[it->first].begin(), rClients[it->first].end());
					waitingLock.unlock();
				}
				rClients[it->first].clear();
				RoomLock.unlock();
				deleteds.push_back(it);
			}
		}
		for (auto d : deleteds)
		{
			rOwner.erase(d);
		}

		OwnerLock.unlock();
	}
}

void Server::RoomNums_Data_Thread()
{
	while (true)
	{
		//added room label vector
		ValueVector PlayerName;
		char recvBuf[BUFLEN];
		vector<SOCKET>::iterator it;
		vector<vector<SOCKET>::iterator> deleteds;
		waitingLock.lock();
		addroom = 0;
		for (it = wClients.begin();it!= wClients.end();++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			if (SOCKET_ERROR != recv(*it, recvBuf, BUFLEN, 0))
			{
				recvBuf[BUFLEN] = '\0';
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
					senJsonParser enJson = senJsonParser( GameData::sRoomData(PlayerName));
					string sendBuf = enJson.encode_RoomData();
					if (SOCKET_ERROR == send(*it, sendBuf.c_str(), sendBuf.length(), 0))
					{
						printf("send room data false for %d\n",*it);
					}
					RoomLock.lock();
					for (auto& c : rClients[rLabel])
					{
						senJsonParser _enJson = senJsonParser(GameData::toValueVector(MyValue(GameData::toValueMap(make_pair(ADDROOM,MyValue(pName))))));
						string _sendBuf = _enJson.encode_aRoomData();
						if (SOCKET_ERROR == send(*it, _sendBuf.c_str(), _sendBuf.length(), 0))
						{
							printf("send room data false for %d\n", *it);
						}
					}
					rClients[rLabel].push_back(*it);
					RoomLock.unlock();
				}
				rClient_names[rLabel].push_back(pName);
				deleteds.push_back(it);
			}
		}

		for (auto d : deleteds)
		{
			wClients.erase(it);
		}

		waitingLock.unlock();
	}
}

void Server::GameData_Thread()
{
	while (true)
	{
		GameLock.lock();
		for (auto cs : gameClients)
		{
			string information;
			for (auto c : cs)
			{
				char recvBuf[BUFLEN];
				ZeroMemory(recvBuf, sizeof(recvBuf));
				if (SOCKET_ERROR != recv(c, recvBuf, sizeof(recvBuf), 0))
				{
					for (auto _c : cs)
					{
						if (_c != c)
						{
							send(_c, recvBuf, BUFLEN, 0);
						}
					}
				}
			}
		}
		GameLock.unlock();
		//rmtx.unlock();
	}

}

//发送数据,超出五秒则不再发送
BOOL Server::send_Ser(SOCKET sClient, string message)
{
	clock_t start = clock();

	while (true)
	{
		//char* sendBuf = const_cast<char*>(information.getSendBuf().c_str());
		if (SOCKET_ERROR == send(sClient, message.c_str(), message.length(), 0))
		{
			//closesocket(sServer);
			//closesocket(sClient);
			//WSACleanup();
			if (clock() - start > TIMEOUTERROR)
			{
				break;
			}
			Sleep(WAITTIME);
			continue;
		}
		break;
	}

	return TRUE;
}

Server::~Server()
{
	closesocket(sServer);
	WSACleanup();
}