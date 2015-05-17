#pragma once

#include "network/Packet.hpp"
#include "network/Outbox.hpp"
#include "objects/ClientData.hpp"
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/PortMapper.hpp>
#include <GFK/System/GameTime.hpp>
#include <enet/enet.h>
#include <string>
#include <functional>

namespace jetGame
{

class NetworkHelper
{
public:
	enum ConnectionType
	{
		Client, Server
	};

	NetworkHelper(ConnectionType ConnectionType);
	~NetworkHelper();

	void StartServer(unsigned short port);
	void ConnectToServer(const std::string &hostName, unsigned short port);
	void DisconnectFromServer();

	void RegisterReceiveHandler(std::function<void (gfk::NetworkBuffer&, unsigned short, ClientData&, const gfk::GameTime&)> handler);
	void RegisterMappingHandler(std::function<void ()> handler);

	void Receive(const gfk::GameTime &gameTime);
	void WritePacket(const Packet &packet, bool reliable);
	void ForEachPeer(std::function<void (const ENetPeer *peer)> handler);
	void ForEachClient(std::function<void (const ClientData &clientData)> handler);
	void Send();

	unsigned int GetPlayerCount();
	unsigned int GetMaxPlayerCount();
	bool IsPortMappingActive();
	IPAddress GetPublicIPAddress();
protected:
private:
	ConnectionType connectionType;
	// We will call this function for each incoming packet
	std::function<void (gfk::NetworkBuffer&, unsigned short, ClientData&, const gfk::GameTime&)> handlePacketFunction;
	std::function<void ()> handleMappingFunction;

	ENetHost *host;
	ENetPeer *serverConnection; // Only for Client types
	Outbox serverOutbox;
	gfk::NetworkBuffer incomingBuffer;
	gfk::PortMapper portMapper; // Only for Server types
	bool automaticPortMapping; // Only for Server types
};

}
