#include <GFK/Network/UDPServer.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>

namespace gfk
{
	UDPServer::UDPServer() :
	listening(false)
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

		listening = socket.Bind(port);
		Logger::Log("UPD Server started");

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

		Logger::Log("UDP Server stopped");
	}

	void UDPServer::Stop()
	{
		listening = false;
	}

}
