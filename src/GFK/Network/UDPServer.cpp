#include <GFK/Network/UDPServer.hpp>
#include <iostream>

namespace gfk
{
	UDPServer::UDPServer()
	{
		UDPSocket::InitializeSocketLayer();
	}

	UDPServer::~UDPServer()
	{

	}

	void UDPServer::Start(unsigned short port)
	{
		// Example of starting a thread with a member function
		// std::thread worker(&UDPServer::Listen, this);

		listening = socket.Open(port);
		std::cout << "UDP Server started" << std::endl;

		IPAddress sender;

		while (listening)
		{
			int byteReadCount = socket.Receive(sender, receiveBuffer, sizeof(receiveBuffer));
			if (!byteReadCount)
			{
				continue;
			}

			std::cout << receiveBuffer << std::endl;
			socket.Send(sender, receiveBuffer, sizeof(receiveBuffer));
		}

		std::cout << "UDP Server stopped" << std::endl;
	}

	void UDPServer::Stop()
	{
		listening = false;
	}

}
