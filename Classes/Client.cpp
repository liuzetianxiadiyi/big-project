#include "Client.h"
#include <ctime>
#include <thread>
#include <algorithm>
#include "cocos2d.h"

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

	//3 准备通信地址  
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = inet_addr("192.168.0.7");
	
	return true;
}

BOOL Client::ConnectServer()
{
	if (SOCKET_ERROR == connect(sHost, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		//cout <<clock()-start;
		closesocket(sHost);
		WSACleanup();
		log("can't connect Server!");
		system("pause");
		return FALSE;
	}

	return TRUE;
}

string Client::recv_Cli()
{
	char recvBuf[BUFLEN];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sHost, recvBuf, BUFLEN, 0))
	{
		//closesocket(sHost);
		//WSACleanup();
		return FALSE;
	}

	return string(recvBuf);
}

BOOL Client::send_Cli(string sendBuf)
{
	clock_t start = clock();
	while (true)
	{
		if (SOCKET_ERROR == send(sHost,sendBuf.c_str(), sendBuf.length(), 0))
		{
			//closesocket(sHost);
			//WSACleanup();
			if (clock() - start > TIMEOUTERROR)
			{
				log("send message %s fail,time out", sendBuf.c_str());
				break;
			}
			Sleep(WAITTIME);
			continue;
		}
		//information.clearSendBuf();
		break;
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
