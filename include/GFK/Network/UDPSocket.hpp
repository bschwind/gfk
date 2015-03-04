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
	bool Bind(unsigned short port, bool blocking = false);
	void Close();
	bool IsOpen() const;
	bool Send(const IPAddress &destination, const void *data, int size);
	int Receive(IPAddress &sender, void *data, int size) const;

	static bool InitializeSocketLayer();
	static void ShutdownSocketLayer();
protected:
private:
	int handle;
	unsigned short socketPort;
	static bool socketsInitialized;
};

}
