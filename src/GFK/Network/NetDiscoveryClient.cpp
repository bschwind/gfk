#include <GFK/Network/NetDiscoveryClient.hpp>
#include <GFK/Network/NetDiscoveryServer.hpp>
#include <GFK/System/GameTime.hpp>
#include <GFK/System/Logger.hpp>

namespace gfk
{

NetDiscoveryClient::NetDiscoveryClient()
{

}

NetDiscoveryClient::~NetDiscoveryClient()
{

}

std::unordered_set<IPAddress> NetDiscoveryClient::FindHosts(unsigned short port, double timeToSpendWaiting)
{
	std::unordered_set<IPAddress> hosts;

	UDPSocket socket;
	socket.Bind(0);

	// The destination will be the broadcast address at first to find the server
	IPAddress destination;
	int validAddress = IPAddress::FromIPV4String(IPAddress::GetBroadcastAddress(), port, destination);

	if (!validAddress)
	{
		Logger::Logf("IP address is not valid\n");
		return hosts;
	}

	Logger::Logf("Broadcast address is %s\n", destination.GetIPV4String().c_str());

	// This is the magic number for NetDiscoveryUtil to actually respond
	unsigned int magicNum = NetDiscoveryServer::MagicNumber;

	NetworkBuffer netBuffer(64);
	netBuffer.WriteUnsignedInt32(magicNum);

	socket.Send(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());

	GameTime gameTime;
	double sentTime = gameTime.GetSystemTime();

	IPAddress responseAddress;
	while (true)
	{
		int byteReadCount = socket.Receive(responseAddress, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (!byteReadCount)
		{
			if (gameTime.GetSystemTime() - sentTime > timeToSpendWaiting)
			{
				break;
			}

			continue;
		}

		Logger::Log("Got a response\n");

		unsigned short responsePort = netBuffer.ReadUnsignedInt16();
		hosts.insert(IPAddress(responseAddress.GetAddress(), responsePort));

		netBuffer.Reset();

		// TODO - Add the ability for clients to specify how many hosts
		//        to wait for, and return when we reach that number.
	}

	return hosts;
}

}
