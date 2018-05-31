#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __CLIENT_H__
#define __CLIENT_H__
#include<iostream>  
#include<WinSock2.h>
#include "Information.h"

//#include <ctime>
//客户端  单例模式

#pragma comment(lib,"WS2_32.lib")  
using namespace std;

#define PORT 9999
#define TIME_LAG 500		//发送和接收信息的时间间隔
#define WAITTIME 100		//发送失败后等待时间
#define TIMEOUTERROR 5000	//超时时间
#define BUFLEN 1024

std::recursive_mutex rmtx;

class Client
{
private:
	WSADATA wsaData;
	SOCKET sHost;
	SOCKADDR_IN addrServer;
	static Client * client;
	explicit Client();
	bool init();
public:
	~Client()
	{
		closesocket(sHost);
		WSACleanup();
		delete client;
	}

	static Client* getInstance();

	BOOL ConnectServer();
	BOOL recv_Cli();
	BOOL send_Cli(string sendBuf);

	void SendThread(string sendBuf);		//建立子进程
	void RecvThread();

	void StartClient();
};
#endif