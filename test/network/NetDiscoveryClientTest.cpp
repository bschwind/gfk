#include <iostream>
#include <GFK/System/GameTime.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/NetDiscoveryClient.hpp>

using namespace gfk;

int main()
{
	GameTime::InitClock();
	UDPSocket::InitializeSocketLayer();

	std::unordered_set<IPAddress> hosts = NetDiscoveryClient::FindHosts(55778, 0.5);
	std::cout << "Found " << hosts.size() << " host(s)" << std::endl;

	for (const IPAddress &elem : hosts)
	{
	    std::cout << elem.GetIPV4String() << ":" << elem.GetPort() << std::endl;
	}

	UDPSocket::ShutdownSocketLayer();

	return 0;
}
