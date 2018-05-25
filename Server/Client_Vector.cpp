#include "Client_Vector.h"

void Room_Client::addMember(string playername, SOCKET client)
{
	clients[playername] = client;
}