#include "JetServer.hpp"
#include "Packets.hpp"
#include "network/Packet.hpp"
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 120),
networkCounter(0),
networkSendsPerSecond(40),
updateCounter(0)
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
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToPlayers(gameTime);
	updateCounter++;
}

void JetServer::UpdateNetwork(const gfk::GameTime &gameTime)
{
	IPAddress sender;

	while (true)
	{
		int numBytesRead = socket.Receive(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (numBytesRead > 0 && numBytesRead >= Packets::PACKET_HEADER_SIZE)
		{
			unsigned int applicationID = netBuffer.ReadUnsignedInt32();
			unsigned int sequence = netBuffer.ReadUnsignedInt32();
			unsigned int ack = netBuffer.ReadUnsignedInt32();
			unsigned int ackBitfield = netBuffer.ReadUnsignedInt32();
			unsigned char numPackets = netBuffer.ReadUnsignedByte();

            std::bitset<32> ackBitset = std::bitset<32>(ackBitfield);

            std::cout << "Packet Header[sequence = " << sequence << ", ack = " << ack << ", ackBitfield = " << ackBitset << ", numPackets = " << static_cast<unsigned int>(numPackets) << "]" << std::endl;

			if (applicationID == Packets::applicationID)
			{
				for (int i = 0; i < numPackets; i++)
				{
					unsigned char protocol = netBuffer.ReadUnsignedByte();
					HandleGamePacket(netBuffer, sender, protocol);
				}
			}
		}
		else
		{
			break;
		}

		netBuffer.Reset();
	}

	netBuffer.Reset();
}

void JetServer::HandleGamePacket(NetworkBuffer &netBuffer, const IPAddress &sender, unsigned char protocol)
{
	std::string senderIP = sender.GetIPV4String();
	std::cout << "Received packet from " << senderIP << std::endl;

	if (protocol == Packets::NEW_DESKTOP_CLIENT)
	{
		std::cout << "Desktop user " << senderIP << " connected" << std::endl;
		connections[senderIP] = RemoteConnection();
		connections[senderIP].clientType = ClientType::DESKTOP;
		connections[senderIP].address = sender;

		unsigned char numPlayers = static_cast<unsigned char>(connections.size());
		connections[senderIP].WritePacket(NewDesktopClientAckPacket(numPlayers));
	}
	else if (protocol == Packets::NEW_ANDROID_CLIENT)
	{
		std::cout << "Android user " << senderIP << " connected" << std::endl;
		connections[senderIP] = RemoteConnection();
		connections[senderIP].clientType = ClientType::ANDROID;
		connections[senderIP].address = sender;

        unsigned char numPlayers = static_cast<unsigned char>(connections.size());
        connections[senderIP].WritePacket(NewDesktopClientAckPacket(numPlayers));
	}
	else if (protocol == Packets::MOVEMENT)
	{
		if (connections.find(senderIP) != connections.end())
		{
			float x = netBuffer.ReadFloat32();
			float y = netBuffer.ReadFloat32();
			float z = netBuffer.ReadFloat32();

			for (auto iter = connections.begin(); iter != connections.end(); ++iter)
			{
				if (iter->second.clientType == ClientType::ANDROID)
				{
					iter->second.WritePacket(MovementPacket(x, y, z));
				}
			}
		}
	}
	else if (protocol == Packets::DISCONNECT)
	{
		if (connections.find(senderIP) != connections.end())
		{
			// sender is in the list of connections
			std::cout << senderIP << " disconnected" << std::endl;
			connections.erase(senderIP);
		}
	}
}

void JetServer::UpdateGame(const gfk::GameTime &gameTime)
{

}

void JetServer::SendStateToPlayers(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		for (auto iter = connections.begin(); iter != connections.end(); ++iter)
		{
			iter->second.SendPackets(socket);
		}

		networkCounter = 1;
	}
	else
	{
		networkCounter++;
	}
}

int main()
{
	JetServer server;
	server.Run();

	return 0;
}
