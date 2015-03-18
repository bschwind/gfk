#include "network/NetworkHelper.hpp"
#include "objects/ClientData.hpp"
#include <GFK/System/Logger.hpp>
#include <iostream>

using namespace gfk;

namespace jetGame
{

NetworkHelper::NetworkHelper(ConnectionType connectionType) :
connectionType(connectionType),
serverOutbox(connectionType == ConnectionType::Server ? 0 : 4096),
incomingBuffer(4096)
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

	// 56K modem with 56 Kbps downstream bandwidth
	// 56K modem with 14 Kbps upstream bandwidth
	host = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

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
				event.peer->data = NULL;
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
				if (connectionType == ConnectionType::Server)
				{
					event.peer->data = new ClientData(4096);
				}
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

				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				clientData = static_cast<ClientData*>(event.peer->data);
				if (clientData)
				{
					Logger::Logf("User %d disconnected\n", clientData->id);
					delete clientData;
				}
				event.peer->data = NULL;
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

void NetworkHelper::WritePacket(const Packet &packet, bool reliable)
{
	if (connectionType == ConnectionType::Client)
	{
		serverOutbox.WritePacket(packet, reliable);
	}
	else
	{
		for (int i = 0; i < host->peerCount; i++)
		{
			ENetPeer *currentPeer = &host->peers[i];
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			{
				continue;
			}

			ClientData &clientData = *static_cast<ClientData*>(currentPeer->data);
			clientData.outbox.WritePacket(packet, reliable);
		}
	}
}

void NetworkHelper::ForEachPeer(std::function<void (const ENetPeer *peer)> handler)
{
	for (int i = 0; i < host->peerCount; i++)
	{
		ENetPeer *currentPeer = &host->peers[i];
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
		{
			continue;
		}

		handler(currentPeer);
	}
}

void NetworkHelper::ForEachClient(std::function<void (const ClientData &clientData)> handler)
{
	for (int i = 0; i < host->peerCount; i++)
	{
		ENetPeer *currentPeer = &host->peers[i];
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
		{
			continue;
		}

		ClientData &clientData = *static_cast<ClientData*>(currentPeer->data);
		handler(clientData);
	}
}

void NetworkHelper::Send()
{
	if (connectionType == ConnectionType::Client)
	{
		serverOutbox.Send(serverConnection);
	}
	else
	{
		for (int i = 0; i < host->peerCount; i++)
		{
			ENetPeer *currentPeer = &host->peers[i];
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			{
				continue;
			}

			ClientData &clientData = *static_cast<ClientData*>(currentPeer->data);
			clientData.outbox.Send(currentPeer);
		}
	}

	enet_host_flush(host);
}

unsigned int NetworkHelper::GetPlayerCount()
{
	return host->connectedPeers;
}

unsigned int NetworkHelper::GetMaxPlayerCount()
{
	return host->peerCount;
}

}
