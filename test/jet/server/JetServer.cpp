#include "JetServer.hpp"
#include "Packets.hpp"
#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 120)
{

}

JetServer::~JetServer()
{

}

void JetServer::Initialize()
{
	gfk::ConsoleGame::Initialize();

	socket.Bind(55777);
}

void JetServer::UnloadContent()
{
	gfk::ConsoleGame::UnloadContent();
}

void JetServer::LoadContent()
{
	gfk::ConsoleGame::LoadContent();
}

void JetServer::Update(const gfk::GameTime &gameTime)
{
	IPAddress sender;
	int numBytesRead = socket.Receive(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

	if (numBytesRead > 0)
	{
		unsigned int applicationID = netBuffer.ReadUnsignedInt32();
		unsigned int sequence = netBuffer.ReadUnsignedInt32();
		unsigned int ack = netBuffer.ReadUnsignedInt32();
		unsigned int ackBitfield = netBuffer.ReadUnsignedInt32();

		if (applicationID == Packets::applicationID)
		{
			unsigned char protocol = netBuffer.ReadUnsignedByte();

			if (protocol == Packets::NEW_CLIENT)
			{
				std::cout << "Someone connected" << std::endl;
				netBuffer.Reset();
				netBuffer.WriteUnsignedByte(1);
				socket.Send(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());
			}
			else if (protocol == Packets::MOVEMENT)
			{
				std::cout << "movement - " << netBuffer.ReadFloat32() << ", " << netBuffer.ReadFloat32() << ", " << netBuffer.ReadFloat32() << std::endl;
			}
		}
	}

	netBuffer.Reset();
}

int main()
{
	JetServer server;
	server.Run();

	return 0;
}
