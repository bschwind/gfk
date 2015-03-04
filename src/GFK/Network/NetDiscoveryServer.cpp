#include <GFK/Network/NetDiscoveryServer.hpp>
#include <GFK/System/Logger.hpp>

namespace gfk
{

NetDiscoveryServer::NetDiscoveryServer() :
listeningPort(0),
portToRespondWith(0),
netBuffer(128)
{

}

NetDiscoveryServer::~NetDiscoveryServer()
{

}

void NetDiscoveryServer::Start(unsigned short listeningPort, unsigned short portToRespondWith)
{
	this->portToRespondWith = portToRespondWith;
	socket.Bind(listeningPort);
}

void NetDiscoveryServer::RespondToDiscoveryRequests()
{
	IPAddress sender;
	netBuffer.Reset();

	int byteReadCount = socket.Receive(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

	// If we got nothing or we did not at least get a 32-bit int, return
	if (!byteReadCount || byteReadCount < 4)
	{
		return;
	}

	// Check to make sure the number sent matches the "magic" number we expect
	unsigned int number = netBuffer.ReadUnsignedInt32();
	if (number != MagicNumber)
	{
		return;
	}

	Logger::Logf("NetDiscoveryServer: %s:%hu requested server port\n", sender.GetIPV4String().c_str(), sender.GetPort());

	netBuffer.Reset();

	// Send the port number to the client
	netBuffer.WriteUnsignedInt16(portToRespondWith);
	socket.Send(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());
}

}
