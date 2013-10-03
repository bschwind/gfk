#include <string>
#include <iostream>
#include <thread>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/UDPServer.hpp>

using namespace gfk;

int main()
{
	UDPServer server;
	server.Start(55777);
	
	return 0;
}
