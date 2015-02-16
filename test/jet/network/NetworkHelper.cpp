#include "network/NetworkHelper.hpp"
#include "objects/ClientData.hpp"
#include <GFK/System/Logger.hpp>
#include <iostream>

using namespace gfk;

namespace jetGame
{

NetworkHelper::NetworkHelper(ConnectionType connectionType) :
connectionType(connectionType),
incomingBuffer(4096),
outgoingBuffer(4096),
headerBuffer(4),
packetCount(0)
{

}

NetworkHelper::~NetworkHelper()
{
	enet_host_destroy(host);
}

void NetworkHelper::StartServer(unsigned short port)
{
	if (connectionType != ConnectionType::Server)
	{
		return;
	}

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;
	host = enet_host_create(&address, 32, 2, 0, 0);

	if (host == NULL)
	{
		Logger::LogErrorf("Unable to create a host on port %d", port);
	}
	else
	{
		Logger::Log("Server started\n");
	}
}

void NetworkHelper::ConnectToServer(const std::string &hostName, unsigned short port)
{
	if (connectionType != ConnectionType::Client)
	{
		return;
	}

	host = enet_host_create(NULL, 1, 2, 0, 0);

	if (host == NULL)
	{
		Logger::LogError("Unable to create an ENet host");
		return;
	}

	ENetAddress address;
	ENetEvent event;
	enet_address_set_host(&address, hostName.c_str());
	address.port = port;

	serverConnection = enet_host_connect(host, &address, 2, 0); // 0 is for initial data

	if (serverConnection == NULL)
	{
		Logger::LogError("No network peers available\n");
		return;
	}

	if (enet_host_service(host, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		Logger::Log("Connected to server successfully!\n");
	}
	else
	{
		enet_peer_reset(serverConnection);
		Logger::LogError("Unable to connect to server");
	}
}

void NetworkHelper::DisconnectFromServer()
{
	if (connectionType != ConnectionType::Client)
	{
		return;
	}

	ENetEvent event;
	enet_peer_disconnect(serverConnection, 0);

	while (enet_host_service(host, &event, 3000) > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Log("Disconected from server\n");
				return;
		}
	}
}

void NetworkHelper::RegisterReceiveHandler(std::function<void (gfk::NetworkBuffer&, unsigned short, ClientData&, const gfk::GameTime&)> handler)
{
	handlePacketFunction = handler;
}

void NetworkHelper::Receive(const gfk::GameTime &gameTime)
{
	ENetEvent event;
	ClientData *clientData;
	unsigned short protocol;
	unsigned short version;
	unsigned short numPackets;
	int serviceReturn = enet_host_service(host, &event, 0);

	while (serviceReturn > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				Logger::Log("Someone connected, creating new ClientData object\n");
				clientData = new ClientData();
				event.peer->data = clientData;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				incomingBuffer.Reset();
				incomingBuffer.PopulateData(event.packet->data, event.packet->dataLength);
				clientData = static_cast<ClientData*>(event.peer->data);

				version = incomingBuffer.ReadUnsignedInt16();
				numPackets = incomingBuffer.ReadUnsignedInt16();
				for (int i = 0; i < numPackets; i++)
				{
					protocol = incomingBuffer.ReadUnsignedInt16();
					if (handlePacketFunction)
					{
						handlePacketFunction(incomingBuffer, protocol, *clientData, gameTime);
					}
				}
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				clientData = static_cast<ClientData*>(event.peer->data);
				if (clientData)
				{
					Logger::Logf("User %d disconnected\n", clientData->id);
					delete clientData;
					Logger::Log("Successfully deleted client data\n");
				}
				break;
			case ENET_EVENT_TYPE_NONE:
				Logger::Log("Nothing happened...");
				break;
			default:
				break;
		}

		serviceReturn = enet_host_service(host, &event, 0);
	}
}

void NetworkHelper::WritePacket(const Packet &packet)
{
	if (packetCount == 0)
	{
		// Write packet header
		outgoingBuffer.Reset();
		WriteHeader(1);

		outgoingBuffer.WriteHeader(headerBuffer);
	}

	packet.WriteToBuffer(outgoingBuffer);
	packetCount++;
}

void NetworkHelper::ForEachPeer(std::function<void (const ENetPeer *peer)> handler)
{
	ENetPeer * currentPeer;

	for (currentPeer = host->peers; currentPeer < &host->peers[host->peerCount]; ++currentPeer)
	{
		if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
		{
			continue;
		}

		handler(currentPeer);
	}
}

void NetworkHelper::Broadcast()
{
	if (packetCount > 0)
	{
		WriteHeader(packetCount);
		outgoingBuffer.WriteHeaderNoCountIncrement(headerBuffer);
		ENetPacket *packet = enet_packet_create(outgoingBuffer.GetDataBuffer(), outgoingBuffer.GetBufferCount(), 0);

		if (connectionType == ConnectionType::Server)
		{
			enet_host_broadcast(host, 0, packet);
		}
		else if (connectionType == ConnectionType::Client)
		{
			enet_peer_send(serverConnection, 0, packet);
		}

		enet_host_flush(host);

		outgoingBuffer.Reset();
		packetCount = 0;
	}
}

void NetworkHelper::WriteHeader(unsigned short numPackets)
{
	headerBuffer.Reset();
	headerBuffer.WriteUnsignedInt16(1); // Version
	headerBuffer.WriteUnsignedInt16(numPackets); // Number of packets
}

}
