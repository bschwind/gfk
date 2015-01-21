#include "JetServer.hpp"
#include "Packets.hpp"
#include "network/Packet.hpp"
#include <GFK/System/Logger.hpp>
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 120),
networkCounter(0),
networkSendsPerSecond(40),
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

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 55777;
	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		Logger::LogError("Unable to create a host on port 55777");
	}
	else
	{
		Logger::Log("Server started\n");
	}
}

void JetServer::LoadContent()
{
	gfk::ConsoleGame::LoadContent();
}

void JetServer::UnloadContent()
{
	gfk::ConsoleGame::UnloadContent();
	enet_host_destroy(server);
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
	ENetEvent event;
	unsigned char protocol;
	int serviceReturn = enet_host_service(server, &event, 0);

	while (serviceReturn > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				Logger::Log("Someone connected\n");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				netBuffer.PopulateData(event.packet->data, event.packet->dataLength);

				protocol = netBuffer.ReadUnsignedByte();
				HandleGamePacket(netBuffer, protocol);
				// todo - loop over all packets, not just the first one
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Log("Someone disconnected\n");
				break;
			case ENET_EVENT_TYPE_NONE:
				Logger::Log("Nothing happened...");
				break;
			default:
				break;
		}

		serviceReturn = enet_host_service(server, &event, 0);
	}

	netBuffer.Reset();
}

void JetServer::HandleGamePacket(NetworkBuffer &netBuffer, unsigned char protocol)
{
	if (protocol == Packets::NEW_DESKTOP_CLIENT)
	{
		Logger::Log("Desktop user connected\n");
	}
	else if (protocol == Packets::NEW_ANDROID_CLIENT)
	{
		Logger::Log("Android user connected\n");
	}
	else if (protocol == Packets::MOVEMENT)
	{
		float x = netBuffer.ReadFloat32();
		float y = netBuffer.ReadFloat32();
		float z = netBuffer.ReadFloat32();

		Logger::Logf("Movement Packet: (%f, %f, %f)\n", x, y, z);
	}
	else if (protocol == Packets::DISCONNECT)
	{
		// sender is in the list of connections
		Logger::Log("Someone wants to disconnect\n");
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
		// todo - broadcast state to all players
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
