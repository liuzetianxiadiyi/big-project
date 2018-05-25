#ifndef __INFORMATION_H__
#define __INFORMATION_H__
#include <iostream>
#define BUFLEN 1024  
using std::string;

class Information
{
private:
	string SendBuf;
	string RecvBuf;
	bool isChanging;
public:
	string & getSendBuf()
	{
		return SendBuf;
	}

	string& getRecvBuf()
	{
		return RecvBuf;
	}
	void setSendBuf(const char* str)
	{
		SendBuf = str;
	}
	void setRecvBuf(const char* str)
	{
		RecvBuf = str;
	}
	void setSendAndRecv(const char * str)
	{
		setSendBuf(str);
		setRecvBuf(str);
	}
	void clearSendBuf()
	{
		SendBuf = "";
	}
	void clearRecvBuf()
	{
		RecvBuf = "";
	}

	bool setisChanging(bool b)
	{
		isChanging = b;
	}
};

#endif