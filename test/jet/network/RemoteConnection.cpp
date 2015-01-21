#include "network/RemoteConnection.hpp"
#include <iostream>

namespace jetGame
{

RemoteConnection::RemoteConnection() :
outgoingBuffer(4096),
numPacketsWritten(0)
{

}

RemoteConnection::RemoteConnection(unsigned int bufferCapacity) :
outgoingBuffer(bufferCapacity),
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
		outgoingBuffer.WriteUnsignedInt16(1); // Version
		outgoingBuffer.WriteUnsignedByte(1); // num packets
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
		numPacketsWritten = 0;
		outgoingBuffer.Reset();
	}
}

}
