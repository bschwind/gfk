#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

int main()
{
	UDPSocket socket;
	static const int length = 256;

	socket.Open(55778);

	std::string message;

	while (true)
	{
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(IPAddress(127,0,0,1,55777), sendBuffer, length);
	}

	return 0;
}
