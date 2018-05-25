#ifndef __CLIENTVECTOR_H__
#define __CLIENTVECTOR_H__

#include<vector>
#include "WinSock2.h"
#include <string>
#include <map>
#include <iostream>
#include <unordered_map>

using std::vector;
using std::string;
using std::pair;
using std::unordered_map;

class Room_Client
{
private:
	unordered_map<string, SOCKET> clients;

public:
	void addMember(string playername, SOCKET client);

};

#endif 