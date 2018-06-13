#include "Server.h"
#include "ctime"
#include "senJsonParser.h"
#include "GameData.h"

Server::Server()
{
	WaitingData = GameData::sWaitngData(0, ValueVector(), false);
	int create = init();
	log("create %d", create);
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
		rmtx.lock();

		memset(&addrClient, 0, sizeof(sockaddr_in));
		int addrClientLen = sizeof(addrClient);

		sClient = accept(sServer, (sockaddr *)&addrClient, &addrClientLen);
		if (INVALID_SOCKET != sClient)
		{
			wClients.push_back(sClient);
			senJsonParser* Json = senJsonParser::createWithArray(WaitingData);
			string sendBuf = Json->encode_WaitingData();
			if (SOCKET_ERROR == send(sClient, sendBuf.c_str(), sendBuf.length, 0))
			{
				log("send waiting data false for %s", inet_ntoa(addrClient.sin_addr));
			}
		}
		rmtx.unlock();

		Sleep(TIME_LAG);
	}
	//++num_Clients;
	return TRUE;
}

//发送数据,超出五秒则不再发送
BOOL Server::send_Ser(SOCKET sClient,string message)
{
	clock_t start = clock();

	while (true)
	{
		//char* sendBuf = const_cast<char*>(information.getSendBuf().c_str());
		if (SOCKET_ERROR == send(sClient, message.c_str(), message.length, 0))
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

void Server::EnterGame_Data_Thread()
{
	while (true)
	{
		rmtx.lock();

		char recvBuf[BUFLEN];
		vector < unordered_map<int, SOCKET>::iterator> deleteds;
		for (unordered_map<int, SOCKET>::iterator it = rOwner.begin();it!=rOwner.end();++it)
		{
			if (SOCKET_ERROR != recv(it->second, recvBuf, sizeof(recvBuf), 0))
			{
				for (auto rc : rClients[it->first])
				{
					if (SOCKET_ERROR == send(rc, recvBuf, sizeof(recvBuf), 0))
					{
						log("send enter data false for %d", rc);
					}
				}
				//put roomClient in gameClient
				sJsonParser* json = sJsonParser::createWithC_str(recvBuf);
				if (json->decode_RoomData)
				{
					gameClients.push_back(rClients[it->first]);
				}
				else
				{
					for (auto rc : rClients[it->first])
					{
						wClients.push_back(rc);
					}
				}
				deleteds.push_back(it);
			}
		}
		for (auto d : deleteds)
		{
			rOwner.erase(d);
		}

		rmtx.unlock();

		Sleep(TIME_LAG);
	}
}

void Server::RoomNums_Data_Thread()
{
	while (true)
	{
		rmtx.lock();

		int addroom = 0;
		ValueVector vLabel;
		ValueVector PlayerName;
		char recvBuf[BUFLEN];
		vector<SOCKET>::iterator it;
		vector<vector<SOCKET>::iterator> deleteds;
		for (it = wClients.begin();it!= wClients.end();++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			if (SOCKET_ERROR != recv(*it, recvBuf, sizeof(recvBuf), 0))
			{
				sJsonParser* json = sJsonParser::createWithC_str(recvBuf);
				json->decode_WaitingData;

				string pName = json->getList().at(0).asValueMap()[PLAYERNAME].asString();
				int rLabel = json->getList().at(0).asValueMap()[ROOMLABEL].asInt();
				rClients[rLabel].push_back(*it);
				if ((json->getList().at(0).asValueMap())[ADDROOM].asBool())
				{
					//记录数据用于Accept线程数据发送
					++addroom;
					vLabel.push_back(Value(rLabel));
				}
				else
				{
					//send some message
					for (auto s : rClient_names[rLabel])
					{
						PlayerName.push_back(Value(s));
					}
					senJsonParser* enJson = senJsonParser::createWithArray( GameData::sRoomData(PlayerName));
					string sendBuf = enJson->encode_RoomData();
					if (SOCKET_ERROR == send(*it, sendBuf.c_str(), sendBuf.length, 0))
					{
						log("send room data false for %d",*it);
					}
				}
				rClient_names[rLabel].push_back(pName);
				deleteds.push_back(it);
			}
		}

		for (auto d : deleteds)
		{
			wClients.erase(it);
		}

		rmtx.unlock();

		Sleep(TIME_LAG);
	}
}

void Server::GameData_Thread()
{
	while (true)
	{
		rmtx.lock();
		for (auto cs : gameClients)
		{
			string information;
			for (auto c : cs)
			{
				char recvBuf[BUFLEN];
				if (SOCKET_ERROR != recv(c, recvBuf, sizeof(recvBuf), 0))
				{

				}
			}
		}

		rmtx.unlock();

		Sleep(TIME_LAG);
	}

}

Server::~Server()
{
	closesocket(sServer);
	WSACleanup();
}