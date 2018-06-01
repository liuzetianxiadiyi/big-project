#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef __CLIENT_H__
#define __CLIENT_H__
#include<iostream>  
#include<WinSock2.h>
#include "Information.h"

//#include <ctime>
//�ͻ���  ����ģʽ

#pragma comment(lib,"WS2_32.lib")  
using namespace std;

#define PORT 9999
#define TIME_LAG 500		//���ͺͽ�����Ϣ��ʱ����
#define WAITTIME 100		//����ʧ�ܺ�ȴ�ʱ��
#define TIMEOUTERROR 5000	//��ʱʱ��
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

	void SendThread(string sendBuf);		//�����ӽ���
	void RecvThread();

	void StartClient();
};
#endif