#pragma once

#include <GFK/Network/SocketHeader.hpp>
#include <GFK/Network/IPAddress.hpp>

namespace gfk
{

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();
	bool Bind(unsigned short port);
	void Close();
	bool IsOpen() const;
	bool Send(const IPAddress &destination, const void *data, int size);
	int Receive(IPAddress &sender, void *data, int size);

	static bool InitializeSocketLayer();
	static void ShutdownSocketLayer();
protected:
private:
	int handle;
	unsigned short socketPort;
	static bool socketsInitialized;
};

}
