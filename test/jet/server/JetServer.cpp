#include "JetServer.hpp"
#include "Packets.hpp"
#include "network/Packet.hpp"
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 120),
networkCounter(0),
networkSendsPerSecond(20),
updateCounter(0),
netBuffer(4096)
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

		if (numBytesRead > 0)
		{
			std::string senderString = sender.GetIPV4String();

			if (connections.find(senderString) == connections.end())
			{
				// If the connection does not yet exist, create it
				connections[senderString] = RemoteConnection();
				connections[senderString].address = sender;
			}

			connections[senderString].HandleIncomingPackets(netBuffer, this);
		}
		else
		{
			break;
		}

		netBuffer.Reset();
	}

	netBuffer.Reset();
}

void JetServer::HandlePacket(NetworkBuffer &netBuffer, const IPAddress &sender, unsigned char protocol)
{
	std::string senderIP = sender.GetIPV4String();
	std::cout << "hahahahaha" << std::endl;

	if (protocol == Packets::NEW_DESKTOP_CLIENT)
	{
		NewDesktopClientPacket packet = NewDesktopClientPacket::ReadFromBuffer(netBuffer);

		std::cout << "Desktop user " << senderIP << " connected" << std::endl;
		std::cout << "Special client data: " << static_cast<short>(packet.number) << std::endl;

		connections[senderIP].clientType = ClientType::DESKTOP;

		unsigned char numPlayers = static_cast<unsigned char>(connections.size());
		connections[senderIP].WritePacketReliable(NewDesktopClientAckPacket(numPlayers));
	}
	else if (protocol == Packets::NEW_ANDROID_CLIENT)
	{
		NewAndroidClientPacket packet = NewAndroidClientPacket::ReadFromBuffer(netBuffer);

		std::cout << "Android user " << senderIP << " connected" << std::endl;
		std::cout << "Special client data: " << packet.number << std::endl;

		connections[senderIP].clientType = ClientType::ANDROID_CLIENT;

		unsigned char numPlayers = static_cast<unsigned char>(connections.size());
		connections[senderIP].WritePacket(NewDesktopClientAckPacket(numPlayers));
	}
	else if (protocol == Packets::JET_INPUT)
	{
		if (connections.find(senderIP) != connections.end())
		{
			for (auto iter = connections.begin(); iter != connections.end(); ++iter)
			{
				if (iter->second.clientType == ClientType::ANDROID_CLIENT)
				{
					// iter->second.WritePacket(packet);
				}
			}
		}
	}
	else if (protocol == Packets::DISCONNECT)
	{
		if (connections.find(senderIP) != connections.end())
		{
			DisconnectPacket packet = DisconnectPacket::ReadFromBuffer(netBuffer);

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
			iter->second.WritePacket(HeartbeatPacket());
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
