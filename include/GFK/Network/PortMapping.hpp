#pragma once

#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <natpmp.h>

namespace gfk
{

class PortMapping
{
public:
	PortMapping();
	~PortMapping();

	void Create(unsigned short localPort);
	bool Update();
	bool IsMapped();
	bool HasError();
	std::string GetError();
	IPAddress GetPublicIPAddress();
protected:
	void RequestPublicIPAddress();
private:
	natpmp_t handle;
	enum State
	{
		UNMAPPED,
		REQUESTING_MAPPING,
		REQUESTING_ADDRESS,
		MAPPED,
		ERROR
	};
	State state;
	int errorCode;

	natpmpresp_t publicResponse;
	natpmpresp_t mappingResponse;
};

}
