#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __CLIENT_H__
#define __CLIENT_H__

#pragma comment(lib,"WS2_32.lib")  
#pragma comment(lib,"wsock32.lib")
#include<WinSock2.h>

#include<iostream>
using namespace std;

#define PORT 9999
#define TIME_LAG 500		//发送和接收信息的时间间隔
#define WAITTIME 100		//发送失败后等待时间
#define TIMEOUTERROR 5000	//超时时间
#define BUFLEN 1024
#define RECIEVE "recieve"

//mutex rmtx;

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
	bool recvMessage(char recv[]);
	BOOL ConnectServer();
	string recv_Cli();
	BOOL send_Cli(string sendBuf);

	void SendThread(string sendBuf);		//建立子进程
	void RecvThread();
};
#endif