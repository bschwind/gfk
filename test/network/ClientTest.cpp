#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		Logger::Log("Please provide a port to bind the client to");
		return 1;
	}

	int portInt = atoi(argv[1]);
	unsigned short port = (unsigned short)portInt;

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	static const int length = 256;

	socket.Bind(port);

	std::string message;

	unsigned char receiveBuffer[length];
	IPAddress sender;
	IPAddress destination;
	int validAddress = IPAddress::FromIPV4String("127.0.0.1", 55777, destination);

	Logger::Log(std::string("Destination is ") + destination.GetIPV4String());

	while (validAddress)
	{
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(destination, sendBuffer, strlen(sendBuffer));

		// Receive an echo from the server
		// while (true)
		// {
		// 	int byteReadCount = socket.Receive(sender, receiveBuffer, sizeof(receiveBuffer));

		// 	if (!byteReadCount)
		// 	{
		// 		continue;
		// 	}

		// 	std::cout << receiveBuffer << std::endl;
		// 	break;
		// }
	}

	UDPSocket::ShutdownSocketLayer();

	return 0;
}