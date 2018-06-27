#include "Client.h"
#include <ctime>
#include <thread>
#include <algorithm>
#include "cocos2d.h"
#include <string>

using std::string;

USING_NS_CC;

Client* Client::client = new Client();

bool Client::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))//成功返回0  
	{
		return FALSE;
	}

	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}

	int iMode = 1;
	int retVal = ioctlsocket(sHost, FIONBIO, (u_long FAR*)&iMode);
	if (retVal == SOCKET_ERROR)
	{
		printf("ioctlsocket failed!\n");
		WSACleanup();
		return -1;
	}

	//3 准备通信地址  
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = inet_addr("192.168.0.6");
	
	return true;
}

BOOL Client::ConnectServer()
{
	while(true)
	{
		int err = connect(sHost, (const sockaddr*)&addrServer, sizeof(addrServer));
		//cout <<clock()-start;
		//closesocket(sHost);
		//WSACleanup();
		if (err == SOCKET_ERROR)
		{
			log("can't connect Server!");
		}
		break;
		//system("pause");
		/*return FALSE;*/
	}
	log("connect!");
	//char recvBuf[BUFLEN];
	//ZeroMemory(recvBuf, sizeof(recvBuf));
	//if (SOCKET_ERROR == recv(sHost, recvBuf, BUFLEN, 0))
	//{
	//	//closesocket(sHost);
	//	//WSACleanup();
	//	log("recv message false");
	//	return FALSE;
	//}
	/*log("%s", recvBuf);*/
	return TRUE;
}

bool Client::recvMessage(char recvBuf[])
{
	while (true)
	{
		ZeroMemory(recvBuf, sizeof(recvBuf));
		if (SOCKET_ERROR == recv(sHost, recvBuf, BUFLEN, 0))
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

string Client::recv_Cli()
{
	char recvBuf[BUFLEN];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sHost, recvBuf, BUFLEN, 0))
	{
		//closesocket(sHost);
		//WSACleanup();
		//log("recv message false");
		return "";
	}
	//log("message: %s", recvBuf);
	log("string: %s", string(recvBuf).c_str());
	log("end");
	if (SOCKET_ERROR == send(sHost, RECIEVE, sizeof(RECIEVE), 0))
	{
		log("connect break off");
	}
	return std::string(recvBuf);
}

BOOL Client::send_Cli(string sendBuf)
{
	if (SOCKET_ERROR == send(sHost, sendBuf.c_str(), sendBuf.length(), 0))
	{
		log("GameScene Send Message false");
	}
	//information.clearSendBuf();
	else
	{
		log("send success");
	}
	return TRUE;
}

Client::Client()
{
	if (!init())
	{
		log("init Client false!");
	}

	if (ConnectServer())
	{
		log("connect Server!");
	}
}

Client* Client::getInstance()
{
	return client;
}

void Client::SendThread(string sendBuf)
{
	while (true)
	{
		send_Cli(sendBuf);
		Sleep(TIME_LAG);
	}
}

void Client::RecvThread()
{
	while (true)
	{
		recv_Cli();
		Sleep(TIME_LAG);
	}
}
