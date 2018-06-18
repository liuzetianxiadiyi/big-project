#include "Server.h"
#include "ctime"
#include "senJsonParser.h"
#include "GameData.h"

Server::Server()
{
	WaitingData = GameData::sWaitngData(0, ValueVector(), false);
	int create = init();
	//log("create %d", create);
}

bool Server::init()		//���init����False����return�˳�����
{
	//num_Clients = 0;
	// ��������ʼ��winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return FALSE;
	}
	//�����׽���
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}

	//�����׽��ַ�����ģʽ 
	unsigned long ul = 1;
	if (SOCKET_ERROR == ioctlsocket(sServer, FIONBIO, (unsigned long*)&ul))
	{
		closesocket(sServer);
		WSACleanup();

		return FALSE;
	}

	// ׼��ͨ�ŵ�ַ
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = INADDR_ANY; //����������������ַ

	if (SOCKET_ERROR == ::bind(sServer, (const sockaddr*)&addrServer, sizeof(SOCKADDR_IN)))		//ʹ��::bind����������ͻ
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

	//�ȴ��ͻ�������
	return TRUE;
}

BOOL Server::AcceptClients()
{
	sockaddr_in addrClient;
	SOCKET sClient;
	while (true)
	{
		//rmtx.lock();

		memset(&addrClient, 0, sizeof(sockaddr_in));
		int addrClientLen = sizeof(addrClient);

		sClient = accept(sServer, (sockaddr *)&addrClient, &addrClientLen);
		if (INVALID_SOCKET != sClient)
		{
			wClients.push_back(sClient);
			senJsonParser Json = senJsonParser(WaitingData);
			string sendBuf = Json.encode_WaitingData();
			if (SOCKET_ERROR == send(sClient, sendBuf.c_str(), sendBuf.length(), 0))
			{
				printf("send waiting data false for %s\n", inet_ntoa(addrClient.sin_addr));
			}
		}
		//rmtx.unlock();

		Sleep(TIME_LAG);
	}
	//++num_Clients;
	return TRUE;
}

//��������,�����������ٷ���
BOOL Server::send_Ser(SOCKET sClient,string message)
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

void Server::EnterGame_Data_Thread()
{
	while (true)
	{
		//rmtx.lock();

		char recvBuf[BUFLEN+1];
		vector < unordered_map<int, SOCKET>::iterator> deleteds;
		for (unordered_map<int, SOCKET>::iterator it = rOwner.begin();it!=rOwner.end();++it)
		{
			if (SOCKET_ERROR != recv(it->second, recvBuf, BUFLEN, 0))
			{
				recvBuf[BUFLEN] = '\0';
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
					//��room��һ��vector�еĿͻ���ȫ������gameClient
					gameClients.push_back(rClients[it->first]);
				}
				else
				{
					wClients.insert(wClients.end(), rClients[it->first].begin(), rClients[it->first].end());
				}
				deleteds.push_back(it);
			}
		}
		for (auto d : deleteds)
		{
			rOwner.erase(d);
		}

		//rmtx.unlock();

		Sleep(TIME_LAG);
	}
}

void Server::RoomNums_Data_Thread()
{
	while (true)
	{
		//rmtx.lock();

		int addroom = 0;
		//added room label vector
		ValueVector vLabel;
		ValueVector PlayerName;
		char recvBuf[BUFLEN+1];
		vector<SOCKET>::iterator it;
		vector<vector<SOCKET>::iterator> deleteds;
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

				rClients[rLabel].push_back(*it);
				if ((json.getRow()[ADDROOM].asBool()))
				{
					//��¼��������Accept�߳����ݷ���
					++addroom;
					vLabel.push_back(MyValue(rLabel));
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
				}
				rClient_names[rLabel].push_back(pName);
				deleteds.push_back(it);
			}
		}

		for (auto d : deleteds)
		{
			wClients.erase(it);
		}

		//rmtx.unlock();

		Sleep(TIME_LAG);
	}
}

void Server::GameData_Thread()
{
	while (true)
	{
		//rmtx.lock();
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

		//rmtx.unlock();

		Sleep(TIME_LAG);
	}

}

Server::~Server()
{
	closesocket(sServer);
	WSACleanup();
}