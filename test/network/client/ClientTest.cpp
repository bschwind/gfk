#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Please provide a port to bind the client to" << std::endl;
		return 1;
	}

	int portInt = atoi(argv[1]);
	unsigned short port = (unsigned short)portInt;

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	static const int length = 256;

	socket.Bind(port);

	std::string message;

	unsigned char receiveBuffer[256];
	IPAddress sender;
	IPAddress destination;
	int validAddress = IPAddress::FromIPV4String("127.0.0.1", 55777, destination);

	std::cout << "Destination is " << destination.GetIPV4String() << std::endl;

	while (validAddress)
	{
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(destination, sendBuffer, length);

		// Receive an echo from the server
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
