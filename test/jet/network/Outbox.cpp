#include "network/Outbox.hpp"
#include <GFK/System/Logger.hpp>
#include <iostream>

using namespace gfk;

namespace jetGame
{

Outbox::Outbox() :
outgoingBufferReliable(0),
outgoingBufferUnreliable(0),
headerBufferReliable(4),
headerBufferUnreliable(4),
packetCountReliable(0),
packetCountUnreliable(0)
{

}

Outbox::Outbox(unsigned int outgoingBufferSize) :
outgoingBufferReliable(outgoingBufferSize),
outgoingBufferUnreliable(outgoingBufferSize),
headerBufferReliable(4),
headerBufferUnreliable(4),
packetCountReliable(0),
packetCountUnreliable(0)
{

}

Outbox::~Outbox()
{

}

void Outbox::WritePacket(const Packet &packet, bool reliable)
{
	if (!reliable)
	{
		if (packetCountUnreliable == 0)
		{
			// Write packet header
			outgoingBufferUnreliable.Reset();
			WriteHeader(1, reliable);

			outgoingBufferUnreliable.WriteHeader(headerBufferUnreliable);
		}

		packet.WriteToBuffer(outgoingBufferUnreliable);
		packetCountUnreliable++;
	}
	else
	{
		if (packetCountReliable == 0)
		{
			// Write packet header
			outgoingBufferReliable.Reset();
			WriteHeader(1, reliable);

			outgoingBufferReliable.WriteHeader(headerBufferReliable);
		}

		packet.WriteToBuffer(outgoingBufferReliable);
		packetCountReliable++;
	}
}

void Outbox::WriteHeader(unsigned short numPackets, bool reliable)
{
	if (!reliable)
	{
		headerBufferUnreliable.Reset();
		headerBufferUnreliable.WriteUnsignedInt16(2); // Version
		headerBufferUnreliable.WriteUnsignedInt16(numPackets); // Number of packets
	}
	else
	{
		headerBufferReliable.Reset();
		headerBufferReliable.WriteUnsignedInt16(2); // Version
		headerBufferReliable.WriteUnsignedInt16(numPackets); // Number of packets
	}
}

void Outbox::Send(ENetPeer *peer)
{
	if (packetCountUnreliable > 0)
	{
		WriteHeader(packetCountUnreliable, false);
		outgoingBufferUnreliable.WriteHeaderNoCountIncrement(headerBufferUnreliable);
		ENetPacket *packet = enet_packet_create(outgoingBufferUnreliable.GetDataBuffer(), outgoingBufferUnreliable.GetBufferCount(), 0);
		
		enet_peer_send(peer, 0, packet);

		Reset(false);
	}

	if (packetCountReliable > 0)
	{
		WriteHeader(packetCountReliable, true);
		outgoingBufferReliable.WriteHeaderNoCountIncrement(headerBufferReliable);
		ENetPacket *packet = enet_packet_create(outgoingBufferReliable.GetDataBuffer(), outgoingBufferReliable.GetBufferCount(), ENET_PACKET_FLAG_RELIABLE);

		enet_peer_send(peer, 1, packet);

		Reset(true);
	}
}

void Outbox::Reset(bool reliable)
{
	if (!reliable)
	{
		packetCountUnreliable = 0;
		headerBufferUnreliable.Reset();
		outgoingBufferUnreliable.Reset();
	}
	else
	{
		packetCountReliable = 0;
		headerBufferReliable.Reset();
		outgoingBufferReliable.Reset();
	}
}

}
