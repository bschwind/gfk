#pragma once

#include "network/Packet.hpp"
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

	void RegisterReceiveHandler(std::function<void (gfk::NetworkBuffer&, unsigned short, const gfk::GameTime&)> handler);

	void Receive(const gfk::GameTime &gameTime);
	void WritePacket(const Packet &packet);
	void Send();
protected:
private:
	ConnectionType connectionType;
	// We will call this function for each eye
	std::function<void (gfk::NetworkBuffer&, unsigned short, const gfk::GameTime&)> handlePacketFunction;

	ENetHost *host;
	ENetPeer *serverConnection; // Only for Client types
	gfk::NetworkBuffer incomingBuffer;
	gfk::NetworkBuffer outgoingBuffer;
	unsigned short packetCount;
};

}
