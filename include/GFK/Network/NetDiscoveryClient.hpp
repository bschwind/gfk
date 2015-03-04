#pragma once

#include <GFK/Network/NetworkBuffer.hpp>
#include <unordered_set>

namespace gfk
{

class UDPSocket;

class NetDiscoveryClient
{
	
public:
	NetDiscoveryClient();
	~NetDiscoveryClient();

	static std::unordered_set<IPAddress> FindHosts(unsigned short port, double timeToSpendWaiting);
protected:
private:
};

}
