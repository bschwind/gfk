#include <GFK/Network/PortMapping.hpp>
#include <GFK/System/Logger.hpp>

namespace gfk
{

PortMapping::PortMapping()
{
	int result = initnatpmp(&handle,
				0 /* automatically detect default gateway */,
				0 /* don't provide a specific gateway address */);
	if (result >= 0)
	{
		state = State::UNMAPPED;
	}
	else
	{
		state = State::ERROR;
		errorCode = result;
	}
}

PortMapping::~PortMapping()
{
	closenatpmp(&handle);
}

void PortMapping::Create(unsigned short localPort)
{
	if (State::UNMAPPED == state)
	{
		int result = sendnewportmappingrequest(&handle,
						       NATPMP_PROTOCOL_UDP,
						       localPort,
						       0, /* automatic public port */
						       7200 /* lifetime (seconds) */);
		if (result >= 0)
		{
			state = REQUESTING_MAPPING;
		}
		else
		{
			state = ERROR;
			errorCode = result;
		}
	}
	else
	{
		// Throw an exception?
	}
}

void PortMapping::RequestPublicIPAddress()
{
	int result = sendpublicaddressrequest(&handle);
	if (result >= 0)
	{
		state = REQUESTING_ADDRESS;
	}
	else
	{
		state = ERROR;
		errorCode = result;
	}
}

bool PortMapping::Update() {
	bool changed = false;
	natpmpresp_t response;
	int result;
	while (REQUESTING_MAPPING == state || REQUESTING_ADDRESS == state)
	{
		result = readnatpmpresponseorretry(&handle, &response);
		if (NATPMP_TRYAGAIN == result)
		{
			break;
		}
		else if (result < 0)
		{
			state = ERROR;
			errorCode = result;
			changed = true;
			break;
		}
		else if (NATPMP_RESPTYPE_UDPPORTMAPPING == response.type)
		{
			mappingResponse = response;
			changed = true;
			RequestPublicIPAddress();
		}
		else if (NATPMP_RESPTYPE_PUBLICADDRESS == response.type)
		{
			publicResponse = response;
			state = MAPPED;
			changed = true;
		}
	}
	return changed;
}

bool PortMapping::IsMapped()
{
	return MAPPED == state;
}

bool PortMapping::HasError()
{
	return ERROR == state;
}

std::string PortMapping::GetError()
{
	if (ERROR == state)
	{
		return std::string (strnatpmperr(errorCode));

	}
	else
	{
		throw std::invalid_argument("not in an error state");
	}
}

IPAddress PortMapping::GetPublicIPAddress()
{
	if (IsMapped())
	{
		IPAddress address (ntohl(publicResponse.pnu.publicaddress.addr.s_addr),
				   mappingResponse.pnu.newportmapping.mappedpublicport);
		return address;
	}
	else
	{
		throw std::invalid_argument("not actively mapped");
	}
}

}
