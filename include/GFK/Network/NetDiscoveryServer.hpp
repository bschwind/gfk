#pragma once

#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

namespace gfk
{

class UDPSocket;

class NetDiscoveryServer
{
	
public:
	NetDiscoveryServer();
	~NetDiscoveryServer();

	static const unsigned int MagicNumber = 4543223;

	void Start(unsigned short listeningPort, unsigned short portToRespondWith);
	void RespondToDiscoveryRequests();
protected:
private:
	unsigned short listeningPort;
	unsigned short portToRespondWith;

	UDPSocket socket;
	NetworkBuffer netBuffer;
};

}
