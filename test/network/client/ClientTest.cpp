#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

int main(int argc, char* argv[])
{
	int portInt = atoi(argv[1]);
	unsigned short port = (unsigned short)portInt;

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	static const int length = 256;

	socket.Open(port);

	std::string message;

	unsigned char receiveBuffer[256];
	IPAddress sender;

	while (true)
	{
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(IPAddress(127,0,0,1,55777), sendBuffer, length);

		while (true)
		{
			int byteReadCount = socket.Receive(sender, receiveBuffer, sizeof(receiveBuffer));

			if (!byteReadCount)
			{
				continue;
			}

			std::cout << receiveBuffer << std::endl;
			break;
		}
	}

	UDPSocket::ShutdownSocketLayer();

	return 0;
}
