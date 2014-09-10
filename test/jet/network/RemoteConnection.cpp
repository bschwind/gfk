#include "network/RemoteConnection.hpp"
#include <iostream>

namespace jetGame
{

RemoteConnection::RemoteConnection() :
timeSinceLastPacket(0.0f),
localSequenceNumber(0),
remoteSequenceNumber(0),
ackBitfield(0),
roundTripTime(0.0f),
numPacketsWritten(0)
{

}

RemoteConnection::~RemoteConnection()
{

}

void RemoteConnection::WritePacket(const Packet &packet)
{
	if (numPacketsWritten == 0)
	{
		// insert placeholder header info
		outgoingBuffer.WriteUnsignedInt32(Packets::applicationID);
		outgoingBuffer.WriteUnsignedInt32(localSequenceNumber); // sequence
		outgoingBuffer.WriteUnsignedInt32(remoteSequenceNumber); // ack
		outgoingBuffer.WriteUnsignedInt32(ackBitfield); // ack bitfield
		outgoingBuffer.WriteUnsignedByte(1);  // num packets
	}

	packet.WriteToBuffer(outgoingBuffer);

	numPacketsWritten++;
}

void RemoteConnection::SendPackets(gfk::UDPSocket &socket)
{
	if (numPacketsWritten > 0)
	{
		// Update num packets sent
		outgoingBuffer.GetDataBuffer()[16] = numPacketsWritten;

		// Socket Send
		socket.Send(address, outgoingBuffer.GetDataBuffer(), outgoingBuffer.GetBufferCount());

		localSequenceNumber++;
		numPacketsWritten = 0;

		outgoingBuffer.Reset();
	}
}

}
