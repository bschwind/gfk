#pragma once

#include "network/Packet.hpp"
#include "objects/ClientData.hpp"
#include <GFK/Network/NetworkBuffer.hpp>
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

	void Receive(const gfk::GameTime &gameTime);
	void WritePacket(const Packet &packet);
	void ForEachPeer(std::function<void (const ENetPeer *peer)> handler);
	void Broadcast();
	void WriteHeader(unsigned short numPackets);
protected:
private:
	ConnectionType connectionType;
	// We will call this function for each eye
	std::function<void (gfk::NetworkBuffer&, unsigned short, ClientData&, const gfk::GameTime&)> handlePacketFunction;

	ENetHost *host;
	ENetPeer *serverConnection; // Only for Client types
	gfk::NetworkBuffer incomingBuffer;
	gfk::NetworkBuffer outgoingBuffer;
	gfk::NetworkBuffer headerBuffer; // For storing the variable packet header
	unsigned short packetCount;
};

}
