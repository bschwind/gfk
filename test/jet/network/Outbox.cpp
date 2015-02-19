#include "network/Outbox.hpp"
#include <GFK/System/Logger.hpp>
#include <iostream>

using namespace gfk;

namespace jetGame
{

Outbox::Outbox() :
outgoingBuffer(0),
headerBuffer(4),
packetCount(0)
{

}

Outbox::Outbox(unsigned int outgoingBufferSize) :
outgoingBuffer(outgoingBufferSize),
headerBuffer(4),
packetCount(0)
{

}

Outbox::~Outbox()
{

}

void Outbox::WritePacket(const Packet &packet)
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

void Outbox::WriteHeader(unsigned short numPackets)
{
	headerBuffer.Reset();
	headerBuffer.WriteUnsignedInt16(2); // Version
	headerBuffer.WriteUnsignedInt16(numPackets); // Number of packets
}

void Outbox::Send(ENetPeer *peer)
{
	if (packetCount > 0)
	{
		WriteHeader(packetCount);
		outgoingBuffer.WriteHeaderNoCountIncrement(headerBuffer);
		ENetPacket *packet = enet_packet_create(outgoingBuffer.GetDataBuffer(), outgoingBuffer.GetBufferCount(), 0);
		
		enet_peer_send(peer, 0, packet);

		Reset();
	}
}

void Outbox::Reset()
{
	packetCount = 0;
	headerBuffer.Reset();
	outgoingBuffer.Reset();
}

}
