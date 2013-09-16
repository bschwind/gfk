#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

int main()
{
	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	static const int length = 256;

	socket.Open(55778);

	std::string message;

	while (true)
	{
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(IPAddress(192,168,1,6,55777), sendBuffer, length);
	}

	UDPSocket::ShutdownSocketLayer();

	return 0;
}
