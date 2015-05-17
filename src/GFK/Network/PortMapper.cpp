#include <GFK/Network/PortMapper.hpp>
#include <GFK/System/Logger.hpp>

namespace gfk
{

PortMapper::PortMapper()
{
	initnatpmp(&handle,
		   0 /* don't override gateway */,
		   0 /* don't specific gateway address */);
}

PortMapper::~PortMapper()
{
	closenatpmp(&handle);
}

void PortMapper::CreatePortMapping(unsigned short localPort)
{
	// TODO: Check our current state to ensure we don't have two
	// outbound requests.
	sendnewportmappingrequest(&handle,
				  NATPMP_PROTOCOL_UDP,
				  localPort,
				  0, /* automatic public port */
				  7200 /* lifetime (seconds) */);
}

void PortMapper::RequestPublicIPAddress()
{
	sendpublicaddressrequest(&handle);
}

bool PortMapper::Update() {
	natpmpresp_t response;
	int result;
	bool anything = false;
	while (true)
	{
		result = readnatpmpresponseorretry(&handle, &response);
		if (result < 0 || result == NATPMP_TRYAGAIN)
		{
			break;
		}

		if (NATPMP_RESPTYPE_PUBLICADDRESS == response.type)
		{
			publicResponse = response;
			hasPublicResponse = true;
			anything = true;
		}
		else if (NATPMP_RESPTYPE_UDPPORTMAPPING == response.type)
		{
			mappingResponse = response;
			hasMappingResponse = true;
			anything = true;
			RequestPublicIPAddress();
		}
	}
	return anything;
}

bool PortMapper::IsActive()
{
	return hasPublicResponse && hasMappingResponse;
}

IPAddress PortMapper::GetPublicIPAddress()
{
	if (IsActive())
	{
		IPAddress address (ntohl(publicResponse.pnu.publicaddress.addr.s_addr),
				   mappingResponse.pnu.newportmapping.mappedpublicport);
		return address;
	}
	else
	{
		throw 1500;
	}
}

}
