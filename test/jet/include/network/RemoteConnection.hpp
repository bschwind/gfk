#pragma once
#include "ClientType.hpp"
#include "network/Packet.hpp"
#include "network/PacketHandler.hpp"
#include <GFK/Network/IPAddress.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/UDPSocket.hpp>

namespace jetGame
{

class RemoteConnection
{
public:
	RemoteConnection();
	RemoteConnection(unsigned int bufferCapacity);
	~RemoteConnection();

	void WritePacketReliable(const Packet &packet);
	void WritePacket(const Packet &packet);
	void SendPackets(gfk::UDPSocket &socket);
	void HandleIncomingPackets(NetworkBuffer &netBuffer, PacketHandler *packetHandler);

	unsigned char clientType; // Look at ClientType.hpp
	gfk::IPAddress address;
	float roundTripTime;

	// Reliable Variables
	gfk::NetworkBuffer outgoingReliableBuffer;
	unsigned int localReliableSequenceNumber;
	unsigned int remoteReliableSequenceNumber;
	unsigned int reliableAckBitfield;

	// Unreliable Variables
	gfk::NetworkBuffer outgoingUnreliableBuffer;
	unsigned int localUnreliableSequenceNumber;
	unsigned int remoteUnreliableSequenceNumber;
protected:
private:
	unsigned char numReliablePacketsWritten;
	unsigned char numUnreliablePacketsWritten;
	float reliableTimeout;
	float unreliableTimeout;
};

}
