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

	void WritePacket(const Packet &packet, bool reliable);
	void Send(ENetPeer *peer);
	void Reset(bool reliable);
protected:
private:
	gfk::NetworkBuffer outgoingBufferReliable;
	gfk::NetworkBuffer outgoingBufferUnreliable;
	gfk::NetworkBuffer headerBufferReliable; // For storing the variable packet header
	gfk::NetworkBuffer headerBufferUnreliable; // For storing the variable packet header
	unsigned short packetCountReliable;
	unsigned short packetCountUnreliable;

	void WriteHeader(unsigned short numPackets, bool reliable);
};

}
