#pragma once

#include "network/Packet.hpp"
#include <enet/enet.h>
#include <GFK/Network/NetworkBuffer.hpp>

namespace jetGame
{

class Outbox
{
public:
	Outbox();
	Outbox(unsigned int outgoingBufferSize);
	~Outbox();

	void WritePacket(const Packet &packet);
	void Send(ENetPeer *peer);
	void Reset();
protected:
private:
	gfk::NetworkBuffer outgoingBuffer;
	gfk::NetworkBuffer headerBuffer; // For storing the variable packet header
	unsigned short packetCount;

	void WriteHeader(unsigned short numPackets);
};

}
