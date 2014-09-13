#pragma once
#include <map>
#include "ClientType.hpp"
#include "network/Packet.hpp"
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

	void WritePacket(const Packet &packet);
	void SendPackets(gfk::UDPSocket &socket);

	ClientType clientType;
	gfk::IPAddress address;
	gfk::NetworkBuffer outgoingBuffer;
	float timeSinceLastPacket;
	int localSequenceNumber;
	int remoteSequenceNumber;
	int ackBitfield;
	float roundTripTime;
	std::map<int, float> timeSentMap;
protected:
private:
	unsigned char numPacketsWritten;
};

}
