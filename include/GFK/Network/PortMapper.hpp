#pragma once

#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <natpmp.h>

namespace gfk
{

class PortMapper
{
public:
	PortMapper();
	~PortMapper();

	bool Update();
	void CreatePortMapping(unsigned short localPort);
	bool IsActive();
	IPAddress GetPublicIPAddress();
protected:
	void RequestPublicIPAddress();
private:
	natpmp_t handle;
	bool hasPublicResponse;
	natpmpresp_t publicResponse;
	bool hasMappingResponse;
	natpmpresp_t mappingResponse;
};

}
