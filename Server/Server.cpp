#include "Server.h"
#include "ctime"

Server::Server()
{
	init();
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
			rmtx.lock();
			wClients.push_back(sClient);
			rmtx.unlock();
		}
		rmtx.unlock();

		Sleep(TIME_LAG);
	}
	//++num_Clients;
	return TRUE;
}


BOOL Server::recv_Ser(SOCKET sClient)
{
	char recvBuf[BUFLEN];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sClient, recvBuf, sizeof(recvBuf), 0))
	{
		//closesocket(sServer);
		//closesocket(sClient);
		//WSACleanup();
		return FALSE;
	}

	information.setSendAndRecv(recvBuf);
	return TRUE;
}

//发送数据
BOOL Server::send_Ser(SOCKET sClient)
{
	clock_t start = clock();

	while (true)
	{
		char* sendBuf = const_cast<char*>(information.getSendBuf().c_str());
		if (SOCKET_ERROR == send(sClient, sendBuf, sizeof(sendBuf), 0))
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

void Server::RoomNums_Data_Thread()
{
	while (true)
	{
		rmtx.lock();

		char recvBuf[BUFLEN];
		vector<SOCKET>::iterator it;
		for (it = wClients.begin();it!= wClients.end();++it)
		{
			ZeroMemory(recvBuf, sizeof(recvBuf));
			if (SOCKET_ERROR != recv(*it, recvBuf, sizeof(recvBuf), 0))
			{
				Room_Nums_Data = recvBuf;
				sJsonParser* json = sJsonParser::createWithC_str(recvBuf);
				json->decode;

				string pName = json->getList().at(0).asValueMap()[PLAYERNAME].asString();
				int rLable = json->getList().at(0).asValueMap()[ROOMLABEL].asInt();
				
				if ((json->getList().at(0).asValueMap())[ADDROOM].asBool())
				{
					++room_nums;
					Room_Client temp_client;
					temp_client.addMember(pName, *it);
					rClients[rLable] = temp_client;
				}
				else
				{
					rClients[rLable].addMember(pName, *it);
					//send some message


				}

				wClients.erase(it);
			}
		}

		rmtx.unlock();

		Sleep(TIME_LAG);
	}
}

vector<SOCKET>& Server::GetwClients()
{
	return wClients;
}

vector<vector<SOCKET>>& Server::GetClient_inGame_Vector()
{
	return Client_inGame_Vector;
}

unordered_map<int, Room_Client>& Server::GetrClients()
{
	return rClients;
}

Server::~Server()
{
	closesocket(sServer);
	WSACleanup();
}