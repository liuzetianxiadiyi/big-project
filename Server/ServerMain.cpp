#include "Server.h"
#include "enJsonParser.h"
#include "JsonParser.h"

#include <thread>

int main()
{
	Server server;
	thread connectThread = thread([&] {server.AcceptClients(); });
	connectThread.detach();

	thread WaitingThread = thread([&] {server.RoomNums_Data_Thread(); });
	WaitingThread.detach();
}