#include "Server.h"
#include "senJsonParser.h"
#include "sJsonParser.h"

#include <thread>

int main()
{
	Server server;
	thread connectThread = thread([&] {server.AcceptClients(); });
	connectThread.detach();

	//server->

	char c;
	cin >> c;

	/*thread WaitingThread = thread([&] {server.RoomNums_Data_Thread(); });
	WaitingThread.detach();

	thread EnterThread = thread([&] {server.EnterGame_Data_Thread(); });
	EnterThread.detach();

	server.GameData_Thread();*/
}