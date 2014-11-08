#include "network/RemoteConnection.hpp"
#include <iostream>

namespace jetGame
{

RemoteConnection::RemoteConnection() :
roundTripTime(0.0f),
outgoingReliableBuffer(4096),
localReliableSequenceNumber(0),
remoteReliableSequenceNumber(0),
reliableAckBitfield(0),
outgoingUnreliableBuffer(4096),
localUnreliableSequenceNumber(0),
remoteUnreliableSequenceNumber(0),
numReliablePacketsWritten(0),
numUnreliablePacketsWritten(0),
reliableTimeout(0.0f),
unreliableTimeout(0.0f)
{

}

RemoteConnection::RemoteConnection(unsigned int bufferCapacity) :
roundTripTime(0.0f),
outgoingReliableBuffer(bufferCapacity),
localReliableSequenceNumber(0),
remoteReliableSequenceNumber(0),
reliableAckBitfield(0),
outgoingUnreliableBuffer(bufferCapacity),
localUnreliableSequenceNumber(0),
remoteUnreliableSequenceNumber(0),
numReliablePacketsWritten(0),
numUnreliablePacketsWritten(0),
reliableTimeout(0.0f),
unreliableTimeout(0.0f)
{

}

RemoteConnection::~RemoteConnection()
{

}

void RemoteConnection::WritePacketReliable(const Packet &packet)
{
	if (numReliablePacketsWritten == 0)
	{
		// insert placeholder header info
		outgoingReliableBuffer.WriteUnsignedInt32(Packets::applicationID + 1);
		outgoingReliableBuffer.WriteUnsignedInt32(localReliableSequenceNumber); // sequence
		outgoingReliableBuffer.WriteUnsignedInt32(remoteReliableSequenceNumber); // ack
		outgoingReliableBuffer.WriteUnsignedInt32(reliableAckBitfield); // ack bitfield
		outgoingReliableBuffer.WriteUnsignedByte(1);  // num packets

		// Insert localReliableSequenceNumber into sent history
	}

	packet.WriteToBuffer(outgoingReliableBuffer);

	numReliablePacketsWritten++;
}

void RemoteConnection::WritePacket(const Packet &packet)
{
	if (numUnreliablePacketsWritten == 0)
	{
		// Insert placeholder header info
		outgoingUnreliableBuffer.WriteUnsignedInt32(Packets::applicationID);
		outgoingUnreliableBuffer.WriteUnsignedInt32(localUnreliableSequenceNumber); // sequence
		outgoingUnreliableBuffer.WriteUnsignedByte(1);  // num packets
	}

	packet.WriteToBuffer(outgoingUnreliableBuffer);

	numUnreliablePacketsWritten++;
}

void RemoteConnection::SendPackets(gfk::UDPSocket &socket)
{
	// We need to maintain a "history" (ring buffer) of packets we have not yet
	// received acks for
	if (numReliablePacketsWritten > 0)
	{
		// Update num packets sent
		outgoingReliableBuffer.GetDataBuffer()[16] = numReliablePacketsWritten;

		// Socket Send
		socket.Send(address, outgoingReliableBuffer.GetDataBuffer(), outgoingReliableBuffer.GetBufferCount());

		localReliableSequenceNumber++;
		numReliablePacketsWritten = 0;

		outgoingReliableBuffer.Reset();
	}

	if (numUnreliablePacketsWritten > 0)
	{
		// Update num packets sent
		outgoingUnreliableBuffer.GetDataBuffer()[8] = numUnreliablePacketsWritten;

		// Socket Send
		socket.Send(address, outgoingUnreliableBuffer.GetDataBuffer(), outgoingUnreliableBuffer.GetBufferCount());

		localUnreliableSequenceNumber++;
		numUnreliablePacketsWritten = 0;

		outgoingUnreliableBuffer.Reset();
	}
}

void RemoteConnection::HandleIncomingPackets(NetworkBuffer &netBuffer, PacketHandler *packetHandler)
{
	unsigned int applicationID = netBuffer.ReadUnsignedInt32();

	if (applicationID == Packets::applicationID + 1)
	{
		// Reliable packet
		unsigned int sequence = netBuffer.ReadUnsignedInt32();
		unsigned int ack = netBuffer.ReadUnsignedInt32();
		unsigned int ackBitfield = netBuffer.ReadUnsignedInt32();
		unsigned char numPackets = netBuffer.ReadUnsignedByte();

		for (int i = 0; i < numPackets; i++)
		{
			unsigned char protocol = netBuffer.ReadUnsignedByte();
			packetHandler->HandlePacket(netBuffer, address, protocol);
		}
	}
	else if (applicationID == Packets::applicationID)
	{
		// Unreliable packet
		unsigned int sequence = netBuffer.ReadUnsignedInt32();
		unsigned char numPackets = netBuffer.ReadUnsignedByte();

		if (sequence > remoteUnreliableSequenceNumber)
		{
			// Only process packets that are later than what we previously received
			// Todo - handle sequence number wrap-around
			remoteUnreliableSequenceNumber = sequence;

			for (int i = 0; i < numPackets; i++)
			{
				unsigned char protocol = netBuffer.ReadUnsignedByte();
				packetHandler->HandlePacket(netBuffer, address, protocol);
			}
		}
	}
}

}
