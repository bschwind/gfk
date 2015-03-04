#include <GFK/Network/SocketHeader.hpp>
#include <GFK/Network/IPAddress.hpp>
#include <GFK/System/Logger.hpp>
#include <NetAdapter.h>
#include <sstream>

namespace gfk
{

IPAddress::IPAddress() :
address(0),
port(0)
{

}

IPAddress::IPAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) :
address((a << 24) | (b << 16) | (c << 8) | d),
port(port)
{

}

IPAddress::IPAddress(unsigned int address, unsigned short port) :
address(address),
port(port)
{

}

IPAddress::~IPAddress()
{

}

unsigned int IPAddress::GetAddress() const
{
	return address;
}

unsigned char IPAddress::GetA() const
{
	return (unsigned char) (address >> 24);
}

unsigned char IPAddress::GetB() const
{
	return (unsigned char) (address >> 16);
}

unsigned char IPAddress::GetC() const
{
	return (unsigned char) (address >> 8);
}

unsigned char IPAddress::GetD() const
{
	return (unsigned char) (address);
}

unsigned short IPAddress::GetPort() const
{
	return port;
}

std::string IPAddress::GetIPV4String() const
{
	std::stringstream ss;

	ss << static_cast<unsigned short>(GetA())
		<< "." << static_cast<unsigned short>(GetB())
		<< "." << static_cast<unsigned short>(GetC())
		<< "." << static_cast<unsigned short>(GetD());

	return ss.str();
}

int IPAddress::FromIPV4String(std::string address, unsigned short port, IPAddress &ipAddress)
{
	// Get a sockaddr_in struct, so we can call inet_pton to parse the address
	struct sockaddr_in sa;
#if defined(PLATFORM_WINDOWS)
	int result = InetPton(AF_INET, address.c_str(), &(sa.sin_addr));
#elif defined(PLATFORM_MAC) || defined(PLATFORM_UNIX) || defined(PLATFORM_ANDROID)
	int result = inet_pton(AF_INET, address.c_str(), &(sa.sin_addr));
#endif

	if (result > 0)
	{
		// inet_pton converts the address to network byte order,
		// so we need to convert it back to host order with ntohl
		ipAddress = IPAddress(ntohl(sa.sin_addr.s_addr), port);
	}

	return result;
}

std::string IPAddress::GetBroadcastAddress()
{
	std::string broadcastAddress;
	pNetAdapterInfo *adapters = new_pNetAdapterInfo();

	if (adapters)
	{
		const NetAdapterInfo* primaryAdapter = get_primary_pNetAdapterInfo(adapters);

		if (primaryAdapter)
		{
			broadcastAddress = std::string(primaryAdapter->Broadcast);
			delete_pNetAdapterInfo(adapters);
		}
	}

	return broadcastAddress;
}

}
