#pragma once

#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/IPAddress.hpp>
#include <unordered_map>
#include <string>
#include <thread>

namespace gfk
{

struct ClientInfo
{
	std::string privateGUID;
	IPAddress address;
};

class UDPServer
{
public:
	UDPServer();
	~UDPServer();

	void Start(unsigned short port);
	void Stop();
protected:
private:
	UDPSocket socket;
	uint applicationID;
	volatile bool listening;
	unsigned char receiveBuffer[256];
	std::unordered_map<std::string, ClientInfo> clientMap;
};

}
