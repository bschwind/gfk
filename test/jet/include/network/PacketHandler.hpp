#pragma once

#include "network/RemoteConnection.hpp"
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

using namespace gfk;

namespace jetGame
{

class PacketHandler
{
public:
	PacketHandler(){};
	~PacketHandler(){};
	virtual void HandlePacket(NetworkBuffer &netBuffer, const IPAddress &sender, unsigned char protocol) = 0;
};

}
