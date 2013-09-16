#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

int main()
{
	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	unsigned char receiveBuffer[256];

	socket.Open(55777);

	IPAddress sender;
	while (true)
	{
		int byteReadCount = socket.Receive(sender, receiveBuffer, sizeof(receiveBuffer));
		if (!byteReadCount)
		{
			continue;
		}

		std::cout << receiveBuffer << std::endl;
	}

	UDPSocket::ShutdownSocketLayer();
	
	return 0;
}
